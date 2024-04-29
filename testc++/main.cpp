#include <iostream>
#include <vector>

typedef struct TT {
    int B;
    int E;
} TT;

class MV {
  public:
    TT t;
    std::vector<TT> VT;

  public:
    MV() {
        t.B = 100;
        t.E = 200;
        VT.push_back(t);
        VT.push_back(t);
        VT.push_back(t);
    }

  public:
    TT & ref(int i) { 
	    TT & x = VT[1];
	    return  x ;}
};

int main() {
    std::vector<TT> vt;

    MV mv;
    TT t = mv.ref(1);

    std::cout << mv.VT[1].B << "   " << mv.VT[1].E << std::endl;
    t.B = 300;
    t.E = 400;
    std::cout << mv.VT[1].B << "   " << mv.VT[1].E << std::endl;
}
