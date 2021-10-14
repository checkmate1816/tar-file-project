#include "zipdir.h"
#include "ui_zipdir.h"
#include <QString>
#include <QFileDialog>
#include <QDebug>
#include "function.h"
#include "finalpath.h"
#include "hint.h"
using namespace std;
zipdir::zipdir(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::zipdir)
{
    ui->setupUi(this);
}

zipdir::~zipdir()
{
    delete ui;
}
string zipdir::tarfile(string path,string newpath)
{
    map<char, int> count;
    map<char, string> finalcode;
    vector<pair<char, int>> weight;
    map<char, int>::iterator search;
    FILE *file;
    file = fopen(path.c_str(), "r");
    char c;
    if (file == NULL)
    {
        qDebug() << "error";
        exit(0);
    }
    do
    {
        c = fgetc(file);
        if (feof(file))
        {
            break;
        }
        search = count.find(c);
        if (search != count.end())
        {
            count[c] = count[c] + 1;
        }
        else
        {
            count.insert(make_pair(c, 1));
        }
    } while (1);//统计所有字符出现个数
    for (auto a : count)
    {
        weight.push_back(pair<char, int>(a.first, a.second));
    }
    sort(weight.begin(), weight.end(), cmp);//将次数由小到大排列
    Node * huffman = build(weight);
    encode(huffman, finalcode);
    FILE *newfile;
    //string newpath="";
    if (newpath == "")
    {
        QString temp;
       finalpath final(temp,this);
       final.exec();
       newpath=temp.toStdString();
    }
    newfile = fopen(newpath.c_str(), "a+");
    header head = { '\0',{'\0'},{'\0'},{'\0'} };
    head.type = '1';
    strcpy(head.source, path.c_str());
    int i = 0;
    for (auto a : finalcode)
    {
        head.content[i] = a.first;
        i++;
        for (int j = 0; j < a.second.size(); i++, j++)
        {
            head.content[i] = a.second[j];
        }
    }
    for (; i < 59; i++)
        head.content[i] = '\0';
    //fputs(head.prefix, newfile);//将哈夫曼表写入文件头
    //fputc('\n', newfile);
    Record content;
    i = 0;
    int j;
    int total = 0;
    rewind(file);
    map<char, string>::iterator findhuff;
    do
    {
        c = fgetc(file);
        if (feof(file))
        {
            if (i == 512)
            {
                for (i = 0; i < 512; i++)
                {
                    fputc(content.block[i], newfile);
                }
            }
            else
            {
                for (; i < 512; i++)
                {
                    content.block[i] = '0';
                }
                for (i = 0; i < 512; i++)
                {
                    fputc(content.block[i], newfile);
                }
            }
            break;
        }
    aa:if (i < 512)
    {
        findhuff = finalcode.find(c);
        for (j = 0; j < findhuff->second.size() && i < 512; j++, i++,total++)
        {
            content.block[i] = findhuff->second[j];
        }
        if (i == 512)//单个字符没有存储完，512字节已满
        {
            for (i = 0; i < 512; i++)
            {
                fputc(content.block[i], newfile);
            }
            memset(content.block, '\0', 512);
            for (i = 0; j < findhuff->second.size(); j++, i++,total++)
            {
                content.block[i] = findhuff->second[j];
            }
        }
    }
       else
    {
        for (i = 0; i < 512; i++)
        {
            fputc(content.block[i], newfile);
        }
        memset(content.block, '\0', 512);
        i = 0;
        goto aa;
    }
    } while (1);//翻译存储
    memset(content.block, '0', 512);//写入文件结尾
    for (i = 0; i < 512; i++)
    {
        fputc(content.block[i], newfile);
    }
    fclose(newfile);
    newfile = fopen(newpath.c_str(), "r");
    fseek(newfile, 0L, SEEK_END);
    int size = ftell(newfile);
    char *temp=new char[size];
    rewind(newfile);
    i = 0;
    do {
        c = fgetc(newfile);
        if (feof(newfile))
        {
            break;
        }
        temp[i] = c;
        i++;
    } while (1);
    //rewind(newfile);
    fclose(newfile);
    newfile = fopen(newpath.c_str(), "w");
    _itoa(total, head.size, 10);
    fwrite(&head, sizeof(header), 1, newfile);
    for (i = 0; i < size; i++)
    {
        fputc(temp[i], newfile);
    }
    //fputs(content.block, newfile);
    //fputs(content.block, newfile);*/
    fclose(file);
    fclose(newfile);
    return newpath;
}
void zipdir::tardir(string path)
{
    vector<string> store;
    store.push_back(path);
    string old = path;
    path = path + "\\*.*";
    HANDLE hFind;
    FILE *tar;
    string newpath;//最终生成文件路径
    qDebug() << "输入最终打包文件路径" << endl;
    QString temp;
   finalpath final(temp,this);
   final.exec();
   newpath=temp.toStdString();
    tar = fopen(newpath.c_str(),"a+");
    //int j;//标记下一个文件夹位置
    WIN32_FIND_DATAA findData;
    hFind = FindFirstFileA(path.c_str(), &findData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        qDebug() << "fail" << endl;
        return;
    }
    do
    {
        if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY && strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, "..") != 0)
        {
            path = old+"\\"+findData.cFileName;
            pack(path, store);
        }
        else if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0 )
            continue;
        else
        {
            path = old+"\\";
            path = path + findData.cFileName;
            store.push_back(path);
        }
    } while (FindNextFileA(hFind, &findData));//将目录下所有文件打包，记录生成的新txt路径
    for (int i = 0; i < store.size(); i++)
    {

        DWORD FileAttr = GetFileAttributesA(store[i].c_str());
        if (FileAttr == FILE_ATTRIBUTE_DIRECTORY)//path为目录的情况
        {
            header tempheader = { '\0',{'\0'},{'\0'}, {'\0'} };
            tempheader.type = '0';
            strcpy(tempheader.source, store[i].c_str());
            _itoa(store.size()- i - 1, tempheader.size, 10);
            fwrite(&tempheader, sizeof(header), 1, tar);//将文件夹头部写入文件中
        }
        else //path为没有打包的文件
        {
            FILE *tempfile = fopen("D:\\temp.txt", "w+");
            tarfile(store[i].c_str(), "D:\\temp.txt");//临时存储生成的打包文件
            rewind(tempfile);
            //FILE *tempfile= fopen(store[i].c_str(), "r");
            fseek(tempfile, 0L, SEEK_END);
            int size = ftell(tempfile);
            char *temp = new char[size];
            rewind(tempfile);
            int a = 0;
            char c;
            do {
                c = fgetc(tempfile);
                if (feof(tempfile))
                {
                    break;
                }
                temp[a] = c;
                a++;
            } while (1);
            for (a = 0; a < size; a++)
            {
                fputc(temp[a], tar);
            }//将已打包的文件写入到总体的文件中去
        }
    }
    fclose(tar);
}

void zipdir::pack(string path, vector<string> &store)
{
    string old = path;
    store.push_back(path);
    path = path + "\\*.*";
    HANDLE hFind;
    WIN32_FIND_DATAA findData;
    hFind = FindFirstFileA(path.c_str(), &findData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        qDebug() << "fail" << endl;
        return;
    }
    do
    {
        if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY && strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, "..") != 0 )
        {
            path = old+"\\";
            path = path + findData.cFileName;
            store.push_back(path);
            pack(findData.cFileName, store);
        }
        else if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0 )
            continue;
        else
        {
            path = old+"\\";
            path = path + findData.cFileName;
            store.push_back(path);
        }
    } while (FindNextFileA(hFind, &findData));
}



void zipdir::on_tardir_clicked()
{
    QString filepath=ui->path->text();
    QFile file(ui->path->text());
    QFileInfo info(file);
    if (info.exists()==false)
     {
         qDebug() << "no file" << endl;
         exit(0);
     }
         tardir(filepath.toStdString());
         hint *a=new hint();
         a->show();
}

void zipdir::on_back_clicked()
{
    delete this;
}

void zipdir::on_toolButton_clicked()
{
    QString filepath=QFileDialog::getExistingDirectory(this,"choose directory","D:\\");
    ui->path->setText(filepath);
}
