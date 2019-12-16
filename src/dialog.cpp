#include "../incl/dialog.hpp"

void dialog::dialog(easy_dial &easy, const string &input,
            vector<string> &answers, nat &numtelf) throw()
{

    answers.push_back(easy.inici());
    for (nat i=0; i < input.size(); ++i){

        
        try
        {
            answers.push_back(easy.seguent(input[i]));
            numtelf = easy.num_telf();
        }
        catch(const std::exception& e)
        {
            numtelf = 0;
            answers.clear();
            answers.push_back(e);
        }        

    }

}   