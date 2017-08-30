//---------------------------------------------------------------------------

#ifndef TeH
#define TeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TButton *Button1;
    TMemo *Memo1;
    TMemo *Memo2;
    TMemo *Memo3;
    TLabel *Label1;
    TEdit *Edit1;
    TLabel *Label2;
    TEdit *Edit2;
    TLabel *Label3;
    TEdit *Edit3;
    TLabel *Label4;
    TEdit *Edit4;
    TLabel *Label5;
    TEdit *Edit5;
    TLabel *Label6;
    TEdit *Edit6;
    TLabel *Label7;
    TEdit *Edit7;
    TLabel *Label8;
    TMemo *Memo4;
    TLabel *Label9;
    TButton *Button2;
    TCheckBox *CheckBox1;
    TLabel *Label10;
    TLabel *Label11;
    TCheckBox *CheckBox2;
    TPanel *Panel1;
    TPanel *Panel2;
    TPanel *Panel3;
    TEdit *Edit8;
    TButton *Button3;
    TMemo *Memo5;
    TCheckBox *CheckBox3;
    TButton *Button4;
    TSaveDialog *SaveDialog1;
    TCheckBox *CheckBox4;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label111;
	TLabel *Label17;
	TLabel *Label16;
	TLabel *Label18;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall CheckBox1Click(TObject *Sender);
    void __fastcall CheckBox2Click(TObject *Sender);
    void __fastcall CheckBox3Click(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
