#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#define clr(ar,vel) memset(ar,vel,sizeof(ar))
#define PB push_back
#define maxint 0x7fffffff
using namespace std;
int ans[100];

const int maxn = 102011;
const int head = 0;
int size;
int col[maxn];
int row[maxn];
int cell[maxn];

int R[maxn], L[maxn], U[maxn], D[maxn];
int S[maxn], C[maxn], O[maxn], H[maxn], X[maxn];

void remove(const int &c) {
    L[R[c]] = L[c]; R[L[c]] = R[c];
    for (int i = D[c]; i != c; i = D[i]) {
        for (int j = R[i]; j != i; j = R[j]) {
            U[D[j]] = U[j]; D[U[j]] = D[j]; --S[C[j]];
        }
    }
}
void resume(const int &c) {
    for (int i = U[c]; i != c; i = U[i]) {
        for (int j = L[i]; j != i; j = L[j]) {
            ++S[C[j]];
            U[D[j]] = j;
            D[U[j]] = j;
        }
    }
    L[R[c]] = c;
    R[L[c]] = c;
}
bool dfs(const int &k) {

    if (R[head] == head) {
        for(int i = 0; i < k; i ++){
            int num, pos;
            num = X[O[i]]/81;
            pos = X[O[i]]%81;
            ans[pos] = num;
        }
//        for(int i = 0; i < 81; i ++) cout << ans[i];cout << endl;
        return true;
    }

    int s(maxint), c;
    for (int t = R[head]; t != head; t = R[t]) {
    //select the column c which has the fewest number of element.
        if (S[t] < s) {
            s = S[t];
            c = t;
        }
    }
    //cout << k << endl;
    remove(c);
    for (int i = D[c]; i != c; i = D[i]) {
        O[k] = i;
        //record the answer.
        for (int j = R[i]; j != i; j = R[j]) {
            remove(C[j]);
        }
        if (dfs(k + 1)) {return true;}
        for (int j = L[i]; j != i; j = L[j]) {
            resume(C[j]);
        }
    }
    resume(c);
    return false;
}

void link(int r,int c)
{
    ++S[C[size]=c];
    D[size]=D[c];
    U[D[c]]=size;
    U[size]=c;
    D[c]=size;
    if(H[r]<0)H[r]=L[size]=R[size]=size;
    else
    {
        R[size]=R[H[r]];
        L[R[H[r]]]=size;
        L[size]=H[r];
        R[H[r]]=size;
    }
    X[size++]=r;
}

void chance(int i, int j, int w, int &c1, int &c2, int &c3, int &c4){
    c1 = 27*(w-1) + i;								// row
    c2 = 27*(w-1) + 9 + j;							// col
    c3 = 27*(w-1) + 18 + (i-1)/3*3 + (j-1)/3 + 1;		// cell
    c4 = 243 + (i-1)*9+ j;
}

void init(int m){
    clr(col,0);
    clr(row,0);
    clr(cell,0);
    clr(ans, -1);
    clr(H, -1);
    for(int i = 0; i <= m; i ++){
        S[i] = 0;
        R[i] = i+1;
        L[i+1] = i;
        U[i] = D[i] = i;
    }
    R[m] = 0;
    L[0] = m;
    size = m+1;
}
string s;
int run(){
    int rownum;
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int c1, c2, c3, c4;
//    getline(cin, s);
//    s="2..4...8....3....2.6..8.4.9..61...3713....5......37......7.49....4..2.5....51.72.";
    init(324);
    rownum = 1;

    int cnt = 0;
    for(int i = 1; i <= 9; i ++){
        for(int j = 1; j <= 9; j ++){
            if(s[cnt] != '0'){
                int w = s[cnt] - '0';
                ans[cnt] = w;
                rownum = i*9+j+81*w-10;
                chance(i, j, w, c1, c2, c3, c4);
                link(rownum,c1);
                link(rownum,c2);
                link(rownum,c3);
                link(rownum,c4);
                row[c1] = 1;
                col[c2] = 1;
                cell[c3] = 1;
            }
            cnt++;
        }
    }
//    int j = 0;

    for(int i = 1; i <= 9; i ++){
        for(int j = 1; j <= 9; j ++){
            if( ans[i*9-9+j-1] == -1){
                for(int w = 1; w <= 9; w ++){
                    chance(i, j, w, c1, c2, c3, c4);
                    if( row[c1] || col[c2] || cell[c3] ) continue;
                    rownum = i*9+j+w*81-10;
                    link(rownum,c1);
                    link(rownum,c2);
                    link(rownum,c3);
                    link(rownum,c4);
                }
            }
        }
    }
    dfs(0);
    return 0;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settings = new QSettings("cbs", "sodu");
    const QRegExp rx("^[1-9]$");
    sodu = new QList < QList <QLineEdit*> >();
    QLineEdit* Num[9][9] =
           {ui->Num11,ui->Num12,ui->Num13,ui->Num14,ui->Num15,ui->Num16,ui->Num17,ui->Num18,ui->Num19
           ,ui->Num21,ui->Num22,ui->Num23,ui->Num24,ui->Num25,ui->Num26,ui->Num27,ui->Num28,ui->Num29
           ,ui->Num31,ui->Num32,ui->Num33,ui->Num34,ui->Num35,ui->Num36,ui->Num37,ui->Num38,ui->Num39
           ,ui->Num41,ui->Num42,ui->Num43,ui->Num44,ui->Num45,ui->Num46,ui->Num47,ui->Num48,ui->Num49
           ,ui->Num51,ui->Num52,ui->Num53,ui->Num54,ui->Num55,ui->Num56,ui->Num57,ui->Num58,ui->Num59
           ,ui->Num61,ui->Num62,ui->Num63,ui->Num64,ui->Num65,ui->Num66,ui->Num67,ui->Num68,ui->Num69
           ,ui->Num71,ui->Num72,ui->Num73,ui->Num74,ui->Num75,ui->Num76,ui->Num77,ui->Num78,ui->Num79
           ,ui->Num81,ui->Num82,ui->Num83,ui->Num84,ui->Num85,ui->Num86,ui->Num87,ui->Num88,ui->Num89
           ,ui->Num91,ui->Num92,ui->Num93,ui->Num94,ui->Num95,ui->Num96,ui->Num97,ui->Num98,ui->Num99};
    QList <QLineEdit*> vec;
    for(int i=0;i<=8;++i){
        for(int j=0;j<=8;++j){
            vec.append(Num[i][j]);
            Num[i][j]->setValidator(new QRegExpValidator(rx,this));
        }
        sodu->append(vec);
        vec.clear();
    }
    if(!settings->value("number").isNull()){
        int yy=0;
        for(int i=0;i<=8;++i){
            for(int j=0;j<=8;++j){
                if(settings->value("number").toList().at(yy)!=0)
                    sodu->at(i).at(j)->setText(settings->value("number").toList().at(yy).toString());
                ++yy;
            }
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    foreach (QList <QLineEdit*> aa, *sodu) {
        foreach (QLineEdit* bb, aa) {
            if(!bb->text().isEmpty()){
                bb->setReadOnly(true);
                bb->setStyleSheet("background-color: rgb(255, 255, 0);");
                char cha=bb->text().toInt()+'0';//if has text,set it readOnly
                s+=cha;
            }else{
                s+="0";
            }
        }
    }
    run();

    int mmmm=0;
    for(int i=0;i<=8;++i){
        for(int j=0;j<=8;++j){
            sodu->at(i).at(j)->setText(QVariant(ans[mmmm++]).toString());
        }
    }
//    QList <QVariant> uuu;
//    for(int i=0;i<=8;++i){
//        for(int j=0;j<=8;++j){
//            uuu.append(number.at(i).at(j));
//        }
//    }
//    settings->setValue("number",uuu);


}

void MainWindow::on_pushButton_2_clicked()
{
    for(int i=0;i<=8;++i){
        for(int j=0;j<=8;++j){
            sodu->at(i).at(j)->clear();
            sodu->at(i).at(j)->setStyleSheet("background-color: rgb(255, 255, 255);");
            sodu->at(i).at(j)->setReadOnly(false);
        }
    }
    settings->clear();
}
