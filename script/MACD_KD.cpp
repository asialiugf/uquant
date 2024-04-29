// --  var --- begin ----------------
int line0 = 0;
int line100 = 100;
int line80 = 80;
int line20 = 20;
int line50 = 50;

int a1 = 9;
int b1 = 3;

int v2 = 4;
int a2 = 9 * v2;
int b2 = 3 * v2;

let x1("ru2301", 1F);  // 初始化一个对象 : futureID, index?, period =1F; object_list[]
let x2("ru2301", 1S);
let x3("fu2305", 1H);

Future("ru2301", 1F);


let rsv1(x1);
let r1(x1);
let k1(x1);

let rsv5(x1);
let r5(x1);
let k5(x1);
let d5(x1);

let dif3(x1);
let x3(x1);
let dea3(x1);

// --  var --- end  ----------------

int onBars() {
    //------KDJ-------
    rsv1 = RSV<TG>(x1, x1.C, a1);  // <TG>  表示托管 : tuoguan !
    r1 = EMA(rsv1, 1);
    k1 = EMA(rsv1, 1);

    rsv5 = RSV<TG>(x1, x1.C, a1);  // <TG>  表示托管 : tuoguan !
    r5 = EMA(rsv5, 55);
    k5 = SMA(r5, b5, 1);
    d5 = EMA(k5, b4);

    //------MACD-------
    int s3 = 12 * v2;
    int l3 = 26 * v2;
    int m3 = 4 * v2;
    dif3 = (EMA(x1.CLOSE, s3) - EMA(x1.CLOSE, l3)) / 1.5;
    x3 = EMA(dif3, 55);
    dea3 = EMA(dif3, m3);
}
