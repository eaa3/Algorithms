#include <fstream>

using std::ifstream;
using std::ofstream;
using std::endl;

int main()
{
    ifstream in("L0Q2.in");
    ofstream out("L0Q2.out");

    char c;
    int count = 0;
    int val = 0;
    int resultPerLine = 0;
    int nLines = 0;

    in >> nLines;

    //Retirando o primeiro '\n' do buffer...
    in.get(c);



    do
    {
        in.get(c);

        if( c != '\n' && !in.eof())
        {
            in.putback(c);

            in >> val;

            resultPerLine += val;
        }
        else
        {
            if(count < nLines) out << "Resultado #" << ( count + 1 ) << ": " << resultPerLine << "." << endl;
            count++;
            resultPerLine = 0;
        }



    }while(!in.eof() || count<nLines);

    out.close();

    return 0;



}


