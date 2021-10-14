#include "zip.h"
#include "ui_zip.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QFileInfo>
#include "function.h"
#include "finalpath.h"
#include <iostream>
#include "hint.h"
using namespace std;
zip::zip(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::zip)
{
    ui->setupUi(this);
}

zip::~zip()
{
    delete ui;
}
string zip::tarfile(string path,string newpath)
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

void zip::on_backtoinitial_clicked()
{
    delete this;
}

void zip::on_toolButton_clicked()
{
    QString filepath=QFileDialog::getOpenFileName(this,"choose file","D:\\","*");
    ui->line->setText(filepath); 
}


void zip::on_tar_clicked()
{
    QString filepath=ui->line->text();
    QFile file(ui->line->text());
    QFileInfo info(file);
    if (info.exists()==false)
     {
         qDebug() << "no file" << endl;
         exit(0);
     }    
         tarfile(filepath.toStdString()); 
         hint *a=new hint();
         a->show();

}
