/*#include "MessengerApp.h"
#include <iostream>

using namespace std;

int main()
{
    MessengerApp app;

    app.run();

    return 0;
}
*/

#include "MessengerGUI.h"
#include <iostream>

using namespace std;

int main() 
{
    MessengerGUI app;
    if (app.init()) 
    {
        app.run();
        app.close();
    } 
    
    return 0;
}
