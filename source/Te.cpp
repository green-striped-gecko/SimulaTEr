//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Te.h"
#include "math.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//parameter
int R;
double So;
double Su;
double OU;
double UO;
double p;
int sess;


//maximale session=10, ansonsten felder vergrößern
const hismax=1024;
const sessmax=10;
double spop[sessmax];

//Mark file strings
AnsiString mark[100];

AnsiString filename;


double f1 (  double S, double p, double T)
{
return S*p*(T);
}
double f2 ( double S, double p, double T)
{
return S*(1-p)*(T);
}
double f3 (  double S, double p, double T)
{
return (1-S)*(T);
}
double f4 (  double S, double T)
{
return S*T;
}
double f5 (  double S, double T)
{
return (1-S)*T;
}

int bin ( AnsiString history)
{
int binary=0;
int len=history.Length();
for (int i=len;i>0;i--)
    {
    if (history.SubString(i,1)=="1") binary+= pow(2,(len-(i)));
    }
return binary;

}



//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{

R=StrToInt(Edit1->Text);
So=StrToFloat(Edit2->Text);
Su=StrToFloat(Edit3->Text);

OU=StrToFloat(Edit4->Text);
UO=StrToFloat(Edit5->Text);
p=StrToFloat(Edit6->Text);
sess=StrToInt(Edit7->Text);
filename="Sim_"+IntToStr(R)+"_"+FloatToStr(So)+"_"+FloatToStr(Su)+"_"+
   FloatToStr(p)+"_"+FloatToStr(OU)+"_"+FloatToStr(UO)+"_"+IntToStr(sess);
Edit8->Text = filename;
Memo1->Clear();
Memo2->Clear();
Memo3->Clear();
Memo4->Clear();


double S,T;
int h,hpre;


AnsiString hist;
AnsiString dummy;



double freq[hismax];
AnsiString hi[hismax];
for (int i=0;i<hismax;i++) {freq[i]=0; hi[i]="";}

//populations-überlebensrate bestimmen
double dead=0;
double alive=0;
double lebend=0;


double N;

int d[sessmax];
//hauptschleife
for (int session=2;session<sess+1;session++)
{

for (int i=1;i<session;i++) {d[i]=1;  }
d[0]=7;
do
{

                hist="";

                for (int i=0;i<session;i++)  hist+=IntToStr(d[i]);

                N=R;
                for (int i=2;i<session+1;i++)  //history durchgehen und berechnen
                    {

                    int pre;
                    int now;
                    hpre=0;
                    h=StrToInt(hist.SubString(i,1));
                    hpre=StrToInt(hist.SubString(i-1,1));


                    if (hpre<4 || hpre==7) pre=1; else pre=0;
                    if (h<4 || h==7) now=1; else now=0;
                    //Statuswechsel???
                    if (pre==1 && now==1)
                       {
                       S=So;
                       T=1-OU;
                       }
                    if (pre==1 &&  now==0)
                       {
                       S=So;
                       T=OU;
                       }
                    if (pre==0 && now==0)
                       {
                       S=Su;
                       T=1-UO;
                       }
                    if (pre==0 &&  now==1)
                       {
                       S=Su;
                       T=UO;
                       }

                    switch (h)
                           {

                           case 1 :  N*=f1(S,p,T);

                           break;

                           case 2:   N*=f2(S,p,T);

                           break;

                           case 3:  N*=f3(S,p,T);
                           dead+=N;
                           i=99;
                           break;

                           case 4: N*= f4(S,T);

                           break;

                           case 5: N*= f5(S,T);
                           dead+=N;
                           i=99;
                           break;
                           } //end switch

                    }
     //Ausgabe


     //hist = AnsiString::StringOfChar('0',sess-hist.Length())+hist;
     if (CheckBox1->Checked==true)  Memo1->Lines->Add(
         AnsiString::StringOfChar('0',sess-hist.Length())+hist+"   "+FloatToStr(N));

     //in Capture histories umwandeln:
     dummy="";
     for (int i=1;i<hist.Length()+1;i++)
     {
     if  (hist.SubString(i,1)==7 || hist.SubString(i,1)==1)
          dummy+="1";
//      else if (hist.SubString(i,1)==4) dummy+="2";   //für echtes multistate modell
          else dummy+="0";
     }
     dummy = AnsiString::StringOfChar('0',sess-dummy.Length())+dummy;
     // gleiche Histories zusammenzählen

     int hnr=bin(dummy);
     freq[hnr]+=N;
     hi[hnr]=dummy;
     if (CheckBox2->Checked==true) Memo2->Lines->Add(dummy+"   "+FloatToStr(N));

     //history um eins erhöhen
     d[session-1]++;
     for (int pp=1; pp<session-1;pp++)
         {
         if (d[session-pp]>5) {d[session-pp]=1; d[session-(pp+1)]++;}
         }
     //history auf dead checken case 3 und 5;
     for (int pp=1; pp<session-1;pp++)
         {
         if (d[pp]==3 || d[pp]==5)
            {
            for (int ppp=pp+1;ppp<session;ppp++) d[ppp]=5;
            }
         }


}  while (hist != "7"+AnsiString::StringOfChar('5', session-1)); //while loop


alive+=500-dead+lebend;
spop[session]=(alive)/(lebend+500);
Memo4->Lines->Add(/*FloatToStr(dead)+"\t"+FloatToStr(alive)+"\t"+*/FloatToStr(spop[session]));
lebend=alive;
alive=0;
dead=0;


} //next - session loop

for (int i=2;i<pow(2,sess);i++)
{

Memo3->Lines->Add(hi[i]+"\t"+FloatToStr(freq[i])+";");
}


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
for (int i=0;i<100;i++) mark[i]="";
int line=5;
// vorderer Teil von Mark-Simulationsfile

//spop eintragen
    AnsiString sp="_ Spop=";
    for (int i=2;i<sess+1;i++) sp+=" §"+FloatToStr(spop[i]);

mark[0]="proc title "+Edit8->Text+sp+";";
mark[1]="proc chmatrix occasions="+IntToStr(sess)+" groups=1 etype=Multistrata strata=2 NoHist hist=300;";
mark[2]="   glabel(1)=Group 1;";
mark[3]="   time interval ";
for (int i=0;i<sess-1;i++) mark[3]+=" 1";
mark[3]+=";";

mark[4]="   strata  1 2;";

// hinterer Teil von Mark-Simulationsfiles
mark[line]="proc estimate link=Sin varest=2ndPart ;"; line++;
mark[line]="     model={So=Su po pu=0 OU UO};";       line++;
if (CheckBox4->Checked)
   {
    mark[line]="     fixed=2;";                              line++;
    mark[line]="      parm(2)="+Edit6->Text+";";    line++;
   }
else
    {
    mark[line]="      fixed=1;";                             line++;
    }
mark[line]="          parm(3)=0;";                       line++;
mark[line]="     group=1 S 1:obs rows="+IntToStr(sess-1)+" cols="+IntToStr(sess-1)+" Triang;"; line++;

for (int i=0;i<sess-1;i++)
    {
    mark[line]="";
    for (int ii=0;ii<sess-(1+i);ii++)
        {
        mark[line]+="   1";
        }
    mark[line]+=";"; line++;
    }
mark[line]="     group=1 S 2:unobs rows="+IntToStr(sess-1)+" cols="+IntToStr(sess-1)+" Triang;"; line++;
for (int i=0;i<sess-1;i++)
    {
    mark[line]="";
    for (int ii=0;ii<sess-(1+i);ii++)
        {
        mark[line]+="   1";
        }
    mark[line]+=";"; line++;
    }
mark[line]="     group=1 p 1:obs rows="+IntToStr(sess-1)+" cols="+IntToStr(sess-1)+" Triang;"; line++;
for (int i=0;i<sess-1;i++)
    {
    mark[line]="";
    for (int ii=0;ii<sess-(1+i);ii++)
        {
        mark[line]+="   2";
        }
    mark[line]+=";"; line++;
    }
mark[line]="     group=1 p 2:unobs rows="+IntToStr(sess-1)+" cols="+IntToStr(sess-1)+" Triang;"; line++;
for (int i=0;i<sess-1;i++)
    {
    mark[line]="";
    for (int ii=0;ii<sess-(1+i);ii++)
        {
        mark[line]+="   3";
        }
    mark[line]+=";"; line++;
    }
mark[line]="     group=1 Psi 1 to 2 rows="+IntToStr(sess-1)+" cols="+IntToStr(sess-1)+" Triang;"; line++;
for (int i=0;i<sess-1;i++)
    {
    mark[line]="";
    for (int ii=0;ii<sess-(1+i);ii++)
        {
        mark[line]+="   4";
        }
    mark[line]+=";"; line++;
    }
mark[line]="     group=1 Psi 2 to 1 rows="+IntToStr(sess-1)+" cols="+IntToStr(sess-1)+" Triang;"; line++;
for (int i=0;i<sess-1;i++)
    {
    mark[line]="";
    for (int ii=0;ii<sess-(1+i);ii++)
        {
        mark[line]+="   5";
        }
    mark[line]+=";"; line++;
    }
mark[line]="     design matrix constraints=5 covariates=5 identity;"; line++;
mark[line]="   blabel(1)=#S;";   line++;
mark[line]="   blabel(2)=#po;";  line++;
mark[line]="   blabel(3)=#pu;";  line++;
mark[line]="   blabel(4)=#OU;";  line++;
mark[line]="   blabel(5)=#UO;";  line++;
mark[line]="   rlabel(1)=#S;";   line++;
mark[line]="   rlabel(2)=#po;";  line++;
mark[line]="   rlabel(3)=#pu;";  line++;
mark[line]="   rlabel(4)=#OU;";  line++;
mark[line]="   rlabel(5)=#UO;";  line++;
mark[line]="proc stop;";         line++;

AnsiString fn=Edit8->Text;
for (int i=4;i>-1;i--) Memo3->Lines->Insert(0,mark[i]);
for (int i=5;i<line;i++) Memo3->Lines->Add(mark[i]);

Memo3->Lines->SaveToFile("d:\\Bernd\\tempemi\\TE\\"+fn+".sim");

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
Memo3->Visible=false;
Memo4->Visible=false;
Memo5->Visible=false;

for (double rSo=0.1;rSo<=1;rSo+=0.2)
    {
for (double rSu=rSo;rSu<=1;rSu+=0.1)
    {
for (double rp=0.2; rp<=1;rp+=0.2)
    {
for (double rOU=0;rOU<=1;rOU+=0.1)
    {
for (double rUO=0;rUO<=1;rUO+=0.1)
    {
    //(Edit Felder) Parameter updaten
    Edit2->Text=FloatToStr(rSo);
    Edit3->Text=FloatToStr(rSu);
    Edit4->Text=FloatToStr(rOU);
    Edit5->Text=FloatToStr(rUO);
    Edit6->Text=FloatToStr(rp);
    Edit2->Refresh();
    Edit3->Refresh();
    Edit4->Refresh();
    Edit5->Refresh();
    Edit6->Refresh();

    //Simulation starten und abspeichern!!!!
    Button1->Click();
    Button2->Click();

    Memo5->Lines->Add("mark i="+filename+".sim o="+filename+".out");


    } //rUO
    } //rOU
    } //rSu
    } //RSo
    } //rp
Memo3->Visible=true;
Memo4->Visible=true;
Memo5->Visible=true;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
Memo1->Visible = !Memo1->Visible;
Memo5->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
Memo2->Visible = !Memo2->Visible;
Memo5->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox3Click(TObject *Sender)
{
Memo5->Visible=CheckBox3->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
if (SaveDialog1->Execute()) Memo5->Lines->SaveToFile(SaveDialog1->FileName);
}
//---------------------------------------------------------------------------


