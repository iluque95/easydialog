#include "../incl/dialog.hpp"

void dialog::dialog(easy_dial &easy, const string &input,
                    vector<string> &answers, nat &numtelf) throw()
{

    answers.push_back(easy.inici());

    nat i=0;
    bool err = false;

    while (i < input.size() and not err)
    {

        try
        {
            if (input[i] == phone::DELETECHAR)
            {
                answers.push_back(easy.anterior());
            }
            else if (input[i] == phone::ENDCHAR)
            {
                answers.push_back(easy.seguent(phone::ENDPREF));
            }
            else
            {
                answers.push_back(easy.seguent(input[i]));
            }

            try
            {
                numtelf = easy.num_telf();
            }
            catch(error e)
            {
                numtelf = 0;
            }

        }
        catch (error e)
        {
            numtelf = 0;
            answers.clear();
            answers.push_back(e.mensaje());
            err = true;
        }

        ++i;
    }
}