#include <QCoreApplication>
#include <iostream>
#include <bdaqctrl.h>
#include "../IOCardControl/iocardcontrol.h"
#include <unistd.h>
#include <cstdlib>

using namespace Automation::BDaq;

//void teste(void);
void teste2(void);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

   // teste();
    teste2();

    std::wcout << "end." << std::endl;
    std::cin.get();
    return a.exec();
}

void teste()
{
    bool result = false;
    bool high   = false;
    bool out1   = false;
    int id = 0;


    IOCardControl * IOCard = new IOCardControl();

    result = IOCard->CheckIOCard();

    if(result)
    {
        std::wcout << "CheckIOCard() returns True !!" << std::endl;
    }
    else
    {
        std::wcout << "CheckIOCard() returns False !!" << std::endl;
    }

    std::wcout << "Number of IOCards: " << IOCard->GetIOCount() << std:: endl;

    std::wcout << "Turning all leds on !!" << std::endl;
    IOCard->Init(true);
    std::cin.get();

    std::wcout << "Turning all leds off !!" << std::endl;
    IOCard->Init(false);
    std::cin.get();


    std::wcout << "\nSetIO(int id, bool high)" << std::endl;

    do
    {
        std::wcout << "select id (0-7):" << std::endl;
        std::cin >> id;
        std::wcout << "select true / false (0 or 1)" << std::endl;
        std::cin >> high;

        IOCard->SetIO(id, high);

        std::wcout << "do again ? (-1 is no)" << std::endl;
        std::cin >> id;

     } while(id > -1);


    std::wcout << "bool GetIO(int id, bool & output)" << std::endl;

    do
    {
        std::wcout << "select id (0-7):" << std::endl;
        std::cin >> id;
        result = IOCard->GetIO(id,out1);
        if(result)
        {
            std::wcout << "Sucess !!" << std::endl;
            if(out1)
            {
                std::wcout << "led " << id << " is ON !" << std::endl;
            }
            else
            {
                std::wcout << "led " << id << " is OFF !" << std::endl;
            }
        }
        else
        {
            std::wcout << "Fail !!" << std::endl;
        }

            std::wcout << "do again ? (-1 is no)" << std::endl;
            std::cin >> id;

        } while(id > -1);

    delete IOCard;

    std::wcout << "Try deviceNumber=2" << std::endl;

    std::cin.get();
    IOCardControl *IOCard2 = new IOCardControl(2);

    result = IOCard2->CheckIOCard();

    if(result)
    {
        std::wcout << "CheckIOCard() returns True !!" << std::endl;
    }
    else
    {
        std::wcout << "CheckIOCard() returns False !!" << std::endl;
    }

    delete IOCard2;
}

///<summary>
/// This method perfors a test
/// </summary>
void teste2()
{
    unsigned int val = 240;
    IOCardControl * IOCard = new IOCardControl(0);

    for(int led = 0; led < 8 ; led ++)
    {
        sleep(1);
        IOCard->SetIO(led, true);
        std::wcout << IOCard->GetIO() << std::endl;
    }

    for(int led = 0; led < 8 ; led ++)
    {
        sleep(1);
        IOCard->SetIO(led, false);
        std::wcout << IOCard->GetIO() << std::endl;
    }

    for(int led = 0; led < 8 ; led ++)
    {
        sleep(1);
        IOCard->SetIO(static_cast<unsigned char>(val));
        std::wcout << IOCard->GetIO() << std::endl;
        val = ~val;
    }

    val = 85;
    for(int led = 0; led < 8 ; led ++)
    {
        sleep(1);
        IOCard->SetIO(static_cast<unsigned char>(val));
        std::wcout << IOCard->GetIO() << std::endl;
        val = ~val;
    }

    for(int led = 0; led < 8 ; led++)
    {
        sleep(1);
        IOCard->SetIO(static_cast<unsigned char>(val));
        std::wcout << IOCard->GetIO() << std::endl;
        val >>= 1;

    }

    val = 0;
    for(int led = 0; led < 8 ; led++)
    {
        sleep(1);
        IOCard->SetIO(static_cast<unsigned char>(val));
        std::wcout << IOCard->GetIO() << std::endl;
        val = rand() % 256;

    }

    IOCard->SetIO(0);
    std::wcout << IOCard->GetIO() << std::endl;

    delete IOCard;
}
