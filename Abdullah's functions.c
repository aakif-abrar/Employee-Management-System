// displays the main menue
void mainmenue()
{
    int loginvalue, loggedinValue;
    system("cls");
    printf("\nWelcome to HR Management System.\n\n");
    printf("Choose from the following options\n1. Login to your Account\n2. Join as Guest\n3. Quit Program\n");
    int userinput = validation(1,3);
    switch (userinput)
    {
    case 1:
        loginvalue = login();
        if(loginvalue == 0)
        {
            loggedinValue = loggedin();
            if(loggedinValue==0)
            {
                system("cls");
                printf("Logged Out Successfully!");
                Sleep(600);
                mainmenue();
            }
            else if(loggedinValue ==2)
            {
                return;
            }
        }
        else if(loginvalue == 2)
        {
            mainmenue();
        }
        else
        {
            return;
        }
        break;
    case 2:
        if(guest() == 2)
        {
            mainmenue();
        }
        break;
    case 3:
        return ;
        break;  
    }
}
// appends one employee detail to a file. returns 0 if successfull, 1 if unsuccessfull or file not opened
int addemploy()
{
    char name[40], ID[10], Title[40];
    float Salary;
    int validationID;
    while(1)
    {
        printf("Enter an Employee Name (*MAX 28 characters)\n");
        scanf("%[^\n]", name);
        while (getchar() != '\n');
        if(strlen(name) <= 28)
        {
            break;
        }
        printf("Name is TOO LONG\n");
    }
    capitalize(name);
    while(1)
    {
        printf("\nEnter the Employee ID\nEmployee ID format: \"XXXX\" X can be a Digit\nFor Example: 0001, 0002, 1000 etc\n");
        scanf("%s", ID);
        while (getchar() != '\n');
        validationID = checkID(ID);
        if(validationID == 0)
        {
            break;
        }
        else if(validationID == 1)
        {
            return 1;
        }
    }
    while(1)
    {
        printf("Enter the Employee Title (*MAX 30 characters)\n");
        scanf("%[^\n]",Title);
        while (getchar() != '\n');
        if( strlen(Title) <= 30)
        {
            break;
        }
        printf("Title TOO LONG\n");
    }
    capitalize(Title);
    while(1)
    {
        printf("Enter the Employee Salary in numbers (*Max 100000000000000)\n");
        int val = scanf("%f", &Salary);
        while (getchar() != '\n');
        if(val == 1 && Salary <= 100000000000000)
        {
            break;
        }
        else if(val == 0)
        {
            printf("Invalid format\n");
        }
        else
        {
            printf("Salary out of RANGE!\n");
        }
    }

    filehandle = fopen("EmployeeDetails.txt", "a");
    if(filehandle == NULL)
    {
        return 1;
    }
    fprintf(filehandle, "%s\n",name);
    fprintf(filehandle, "%s\n",ID);
    fprintf(filehandle, "%s\n",Title);
    fprintf(filehandle, "%.2f\n",Salary);
    fclose(filehandle);
    return 0;

}
// Capitalizes first letter of every word and uncapitalizes rest
void capitalize(char *string) 
{
    if (string == NULL)
    {
    return;
    } 

    int capitalize_next = 1;

    for (int i = 0; string[i] != '\0'; i++) 
    {
        if (string[i] == ' ') 
        {
            capitalize_next = 1;
        } 
        else if (isalpha(string[i])) 
        {
            if (capitalize_next) 
            {
                string[i] = toupper(string[i]);
                capitalize_next = 0;
            } 
            else 
            {
                string[i] = tolower(string[i]);
            }
        } 
        else 
        {
            capitalize_next = 0;
        }
    }
}
// checks if files open correctly.returns 0 if successfull, 1 if file not opened
int testfiles()
{
    int flag = 0;
    filehandle = fopen("LoginDetails.txt","r");
    if (filehandle == NULL)
    {
        flag = 1;
    }
    fclose(filehandle);
    filehandle = fopen("EmployeeDetails.txt","r");
    if (filehandle == NULL)
    {
        flag = 1;
    }
    fclose(filehandle);
    return flag;
}
// Creates files if they do not exist. Writes login details of 3 members
void createfiles()
{
    system("cls");
    printf("\nCreating \"LoginDetails.txt\"..\n");
    Sleep(800);
    printf("\"LoginDetails.txt\" Created Successfully!\n");
    Sleep(800);
    printf("Creating \"EmployeeDetails.txt\"..\n");
    Sleep(800);
    printf("\"LoginDetails.txt\" Created Successfully!\n");
    Sleep(1000);
    filehandle = fopen("LoginDetails.txt", "w");
    fprintf(filehandle, "aakif\n0889\nabdullah\n0532\nrafay\n0728\n");
    fclose(filehandle);
    filehandle = fopen("EmployeeDetails.txt","w");
    fprintf(filehandle, "Mushtaq Ahmed\n0003\nSoftware Engineer\n54223.50\n");
    fprintf(filehandle, "Saleem Chaudhary\n0008\nData Analyst\n12356.76\n");
    fprintf(filehandle, "Mujeeb Ahmed\n0007\nManager\n98576.45\n");
    fprintf(filehandle, "Ali Jutt\n0005\nHR Specialist\n76754.30\n");
    fprintf(filehandle, "Rafay Mangrio\n0004\nIT Specialist\n65443.25\n");
    fprintf(filehandle, "Abdullah Bukhtar\n0010\nSecurity Guard\n20121.80\n");
    fprintf(filehandle, "Sara Khan\n0002\nMarketing Manager\n87565.90\n");
    fprintf(filehandle, "Fahad Ali\n0001\nData Scientist\n12345.67\n");
    fprintf(filehandle, "Ayesha Shah\n0009\nWeb Developer\n10234.50\n");
    fprintf(filehandle, "Omer Farooq\n0006\nUX Designer\n87675.55\n");

    fclose(filehandle);
}


