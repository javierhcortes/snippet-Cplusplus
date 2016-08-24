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
