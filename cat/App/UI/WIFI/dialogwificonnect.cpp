#include "dialogwificonnect.h"
#include "ui_dialogwificonnect.h"
#include <QKeyEvent>
#include "dialogconnectmask.h"
#include "../../../Base/base.h"


DialogWIFIConnect::DialogWIFIConnect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWIFIConnect)
{
    ui->setupUi(this);
    ui->WIFIPwd->installEventFilter(this);
    setWIFIPwdStrLen(32);
}



DialogWIFIConnect::~DialogWIFIConnect()
{
    delete ui;
}

void DialogWIFIConnect::setWIFIPwdStrLen(int vel)
{
    WIFIPwdStrLen = vel;
}

void DialogWIFIConnect::on_btn_shift_clicked()
{
    isSHIFT = !isSHIFT;
    if(isSHIFT){
        ui->btn_shift->setText("SHIFT");
    }else{
        ui->btn_shift->setText("shift");
    }
}

void DialogWIFIConnect::on_btn_space_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    WIFIPwdStr += " ";
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_Baskspace_clicked()
{
    if(WIFIPwdStr.length() == 0){
        return;
    }
    WIFIPwdStr.chop(1);
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_lang_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "~";
    }else{
        WIFIPwdStr += "`";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_1_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "!";
    }else{
        WIFIPwdStr += "1";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_2_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "@";
    }else{
        WIFIPwdStr += "2";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_3_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "#";
    }else{
        WIFIPwdStr += "3";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_4_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "$";
    }else{
        WIFIPwdStr += "4";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_5_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "%";
    }else{
        WIFIPwdStr += "5";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_6_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "^";
    }else{
        WIFIPwdStr += "6";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_7_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "&";
    }else{
        WIFIPwdStr += "7";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_8_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "*";
    }else{
        WIFIPwdStr += "8";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_9_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "(";
    }else{
        WIFIPwdStr += "9";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_0_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += ")";
    }else{
        WIFIPwdStr += "0";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_jian_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "_";
    }else{
        WIFIPwdStr += "-";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_deng_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "+";
    }else{
        WIFIPwdStr += "=";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_q_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "Q";
    }else{
        WIFIPwdStr += "q";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_w_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "W";
    }else{
        WIFIPwdStr += "w";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_e_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "E";
    }else{
        WIFIPwdStr += "e";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_r_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "R";
    }else{
        WIFIPwdStr += "r";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_t_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "T";
    }else{
        WIFIPwdStr += "t";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_y_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "Y";
    }else{
        WIFIPwdStr += "y";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_u_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "U";
    }else{
        WIFIPwdStr += "u";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_i_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "I";
    }else{
        WIFIPwdStr += "i";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_o_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "O";
    }else{
        WIFIPwdStr += "o";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_p_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "P";
    }else{
        WIFIPwdStr += "p";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_zuokuang_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "{";
    }else{
        WIFIPwdStr += "[";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_youkuang_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "}";
    }else{
        WIFIPwdStr += "]";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_fanxie_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "|";
    }else{
        WIFIPwdStr += "\\";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_a_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "A";
    }else{
        WIFIPwdStr += "a";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_s_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "S";
    }else{
        WIFIPwdStr += "s";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_d_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "D";
    }else{
        WIFIPwdStr += "d";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_f_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "F";
    }else{
        WIFIPwdStr += "f";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_g_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "G";
    }else{
        WIFIPwdStr += "g";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_h_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "H";
    }else{
        WIFIPwdStr += "h";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_j_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "J";
    }else{
        WIFIPwdStr += "j";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_k_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "K";
    }else{
        WIFIPwdStr += "k";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_l_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "L";
    }else{
        WIFIPwdStr += "l";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_fenhao_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += ":";
    }else{
        WIFIPwdStr += ";";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_danyin_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "\"";
    }else{
        WIFIPwdStr += "'";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_z_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "Z";
    }else{
        WIFIPwdStr += "z";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_x_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "X";
    }else{
        WIFIPwdStr += "x";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_c_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "C";
    }else{
        WIFIPwdStr += "c";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_v_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "V";
    }else{
        WIFIPwdStr += "v";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_b_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "B";
    }else{
        WIFIPwdStr += "b";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_n_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "N";
    }else{
        WIFIPwdStr += "n";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_m_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "M";
    }else{
        WIFIPwdStr += "m";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_douhao_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "<";
    }else{
        WIFIPwdStr += ",";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_jvhao_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += ">";
    }else{
        WIFIPwdStr += ".";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btn_xiegang_clicked()
{
    if(WIFIPwdStr.length() > WIFIPwdStrLen){
        return;
    }
    if(isSHIFT){
        WIFIPwdStr += "?";
    }else{
        WIFIPwdStr += "/";
    }
    ui->WIFIPwd->setText(WIFIPwdStr);
}

void DialogWIFIConnect::on_btnConnect_clicked()
{
    DialogConnectMask diaConnect(this);
    connectUi = &diaConnect;
    diaConnect.exec();
    connectUi = nullptr;
}
