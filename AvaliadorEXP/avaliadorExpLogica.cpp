#include <iostream>
#include <string>

using namespace std;


struct InfoExp
{
    string dir;
    string esq;
    char op;
    bool val;
};

bool x,y,z;
InfoExp val(string);


int main ()
{
    string exp;

    //cout << "Valores!" << endl;
    //cin >> x >> y >> z;

    cout << "\n Expressao" << endl;

	cin >> exp;


	InfoExp ret = val(exp);

    cout << "Esq: " << ret.esq << " Dir: " << ret.dir << endl;
    //cout << "Valor= " << ret.val << endl;
    cin.get();
    cin.get();

    return 0;


}

InfoExp val(string exp)
{
    InfoExp ret;

    if(exp[0] == '-')
    {
        ret.op = exp[0];
        ret.dir = exp.substr(1);

        ret.val = !x;
    }
    else
    {
        int countDir,countEsq,dif,i;
        i = dif = countDir = countEsq = 0;
        bool zerou = false;


        while( !zerou && i< exp.size() )
        {
            if(exp[i] == '(') countDir++;
            else if(exp[i] == ')') countEsq++;

            dif = (countDir - countEsq);
            zerou = (dif==0);
            i++;
        }

        ret.op = exp[i+1];
        ret.dir = exp.substr(i+1);
        ret.esq = exp.substr(0,i);

        InfoExp e1,e2;
        bool val1,val2

        if(ret.dir.size() == 1)
        {
            if(ret.dir[0] == 'x')
            {
                val1 = x;
            }
            else if(ret.dir[0] == 'y')
            {
                val1 = y;
            }
            else if(ret.dir[0] == 'z')
            {
                val1 = z;
            }
        }


    }

    return ret;
}
