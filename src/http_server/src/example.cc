//********************************************************
/**
 * @file  example2.cc 
 *
 * @brief libnavajo example code.
 *
 * @author T.Descombes (descombes@lpsc.in2p3.fr)
 *
 * @version 1  
 * @date 27/01/15
 */
//********************************************************

#include <signal.h> 
#include <string.h> 
#include "libnavajo/libnavajo.hh"
#include "libnavajo/LogStdOutput.hh"


#include "ros/ros.h"
#include "std_msgs/String.h"


WebServer *webServer = NULL;
char message[255];
void exitFunction( int dummy )
{
   if (webServer != NULL) webServer->stopService();
}

/***********************************************************************/

class MyDynamicRepository : public DynamicRepository
{
    class MyDynamicPage : public DynamicPage
    {
      protected:
        bool isValidSession(HttpRequest* request)
        {
          void *myAttribute = request->getSessionAttribute("username");          
          return myAttribute != NULL;
        }
    };
    
    class Auth: public MyDynamicPage
    {
      bool getPage(HttpRequest* request, HttpResponse *response)
      {
	std::string login, password;
        // User libnavajo/libnavajo is allowed
        if (request->getParameter("login", login) && request->getParameter("pass", password)
            && (login == "libnavajo" && password == "libnavajo"))
        {
          char *username = (char*)malloc((login.length()+1)*sizeof(char));
          strcpy(username, login.c_str());
          request->setSessionAttribute ( "username", (void*)username );
          return fromString("authOK", response);
        }
        return fromString("authBAD", response);
      } 
    } auth;

    class Controller: public MyDynamicPage
    {
      bool getPage(HttpRequest* request, HttpResponse *response)
      {
	std::string param;

        if (request->getParameter("pageId", param) && param == "LOGIN" && isValidSession(request))
        {
          response->forwardTo("gauge.html"); 
          return true;
        } 

        if (request->hasParameter("disconnect")) // Button disconnect
          request->removeSession();

        if (!isValidSession(request))
          response->forwardTo("login.html");
        else
          response->forwardTo("gauge.html");       
        
        return true;
      }

    } controller;
    
    class AJAX: public MyDynamicPage
	{
	  bool getPage(HttpRequest* request, HttpResponse *response)
	  {
            std::ostringstream content;
	    content << message;
            fromString(content.str(),response);
	    return true;
	  }

	} ajax;
	    
  public:
    MyDynamicRepository() : DynamicRepository()
    {
      add("index.html",&controller);
      add("auth.txt",&auth);
      add("ajax_info.txt",&ajax);
    }
};

/***********************************************************************/

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
     memset(message,'\0',255);
     strcpy(message,msg->data.c_str());
}

int main(int argc, char **argv)
{
  // connect signals
  signal( SIGTERM, exitFunction );
  signal( SIGINT, exitFunction );
  
  NVJ_LOG->addLogOutput(new LogStdOutput);
  webServer = new WebServer;
  //webServer->setUseSSL(true, "../myCert.pem");
  LocalRepository myLocalRepo("", "/home/xillinux/cobot/catkin_ws/html");
  webServer->addRepository(&myLocalRepo);
  webServer->setServerPort(8000);
  MyDynamicRepository myRepo;
  webServer->addRepository(&myRepo);

  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
  
  webServer->startService();
  //webServer->wait();
  ros::spin();
  LogRecorder::freeInstance();
  return 0;
}


