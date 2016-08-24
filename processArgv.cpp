int main(int argc, char** argv)
{
  /// Cantidad de Argumentos de entrada
  cout << CLR_OK << flush;
  if (argc < 2 || argc > 4){
    showHelpInfo(argv[0]);
    cout << CLR_OK << endl;
    return EXIT_FAILURE;
  }

  bool debugConsole = false;
  bool showHelp = false;
  bool showVersion = false;
  int c;
  char *cvalue = 0;

  while ((c = getopt (argc, argv, "hvd:")) != -1)
  switch (c)
  {
    case 'h':  showHelp = true;                 break;
    case 'v':  showVersion = true;              break;
    case 'd':  debugConsole = true;
               cvalue = optarg;                 break;
    case '?':
      if (optopt == 'd')
        fprintf (stderr, "Option -%c requires an argument.\n", optopt);
      else if (isprint (optopt))
        fprintf (stderr, "Unknown option `-%c'.\n", optopt);
      else
        fprintf (stderr, "Unknown option character `\\x%x'.\n",   optopt);
      return EXIT_FAILURE;
  }

  /*
  printf ("debugflag = %d, help = %d, showVer = %d cvalue = %s\n", debugConsole, showHelp, showVersion, cvalue );
  for (int index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);
  */

  //showProto();

  if (showHelp){showHelpInfo(argv[0]); return EXIT_SUCCESS;}

  if (showVersion){
    showVer();
    return EXIT_SUCCESS;
  }
}


void showHelpInfo(char *s)
{
  cout << CLR_OK << "Usage:  " << s << " [-option] [DataBase Name]" << endl;
  cout <<  "option: " << "-h show help information" << endl;
  cout <<  "        " << "-d enable debug console in /etc/zeus/console-debug.conf" << endl;
  cout <<  "        " << "-v show version information" << CLR_OK <<  endl;
}

string printHora()
{
  time_t now = time(0);
  std::string t(ctime(&now));
  std::string t2 = t.substr(0, t.length() - 1);

  return t2;
}

// Code taken from: http://www.gamedev.net/community/forums/topic.asp?topic_id=459511
std::string getExePath()
{
  // get directory
  string fullFileName = "";
  std::string path = "";
  pid_t pid = getpid();
  char buf[20] = {0};
  sprintf(buf,"%d",pid);
  std::string link = "/proc/";
  link.append( buf );
  link.append( "/exe");
  char proc[512];
  int ch = readlink(link.c_str(), proc, 512);
  if (ch != -1)
  {
    proc[ch] = 0;
    path = proc;
    std::string::size_type t = path.find_last_of("/");
    path = path.substr(0,t);
  }
  fullFileName = path + string("/");
  return fullFileName;
}


std::string executeInShell(string cmd)
{
  string data;
  FILE * stream;
  const int max_buffer = 2048;
  char buffer[max_buffer];
  //cmd.append(" 2>&1"); // Do we want STDERR?

  stream = popen(cmd.c_str(), "r");
  if (stream)
  {
    while (!feof(stream))
    if (fgets(buffer, max_buffer, stream) != NULL)
    data.append(buffer);
    pclose(stream);
  }
  return data;
}


/// Obtencion de Unidades Puerto Serie

  int validcmd;
  if(debugConsole)  validcmd = system("grep -v '^#' /etc/zeus/console-debug.conf > /dev/null");
  else              validcmd = system("find /dev/serial/by-id/ | grep USBSICOM > /dev/null");

  if (validcmd != 0 ){
    cout << CLR_BOOM << (debugConsole ? "Archivo console-debug.conf no encontrado/comentado(#)" : "Ningun USB-SICOM Conectado") << CLR_OK << endl;
    mysql_library_end();
    return EXIT_FAILURE;
  }

  string amountSerialPortFind;
  if(debugConsole) amountSerialPortFind = executeInShell("grep -v '^#' /etc/zeus/console-debug.conf | grep -c /dev/");
  else             amountSerialPortFind = executeInShell("find /dev/serial/by-id/ | grep -c USBSICOM");
  
  
  
  int MenuClass::getConsoleValue(int minValue, int maxValue)
{
  int n = 0;

  while (true)
  {
    cin >> n;
    if (std::cin.fail())
    {
      cout << "Valor Ingresado no valido," << endl;
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    if (n < minValue || n > maxValue)
    {
      cout << "Valor fuera de Rango..." << endl;
      continue;
    }
    cout << CLR_BLAC2 << "Valor ingresado : " << dec <<  n  << CLR_OK << endl;
    return n;
  }
  return n;
}
