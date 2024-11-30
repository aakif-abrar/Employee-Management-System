// creates a new account and add it to the file. returns 0 if successful, 1 if file not opened and 2 if user wants to go back
int createAccount()
{
    char username[50], pass1[50], pass2[50], line[50];
    printf("\nEnter the Username\n*Username should be without ANY spaces\n");
    scanf("%s", username);
    filehandle = fopen("LoginDetails.txt", "r");
    while (fgets(line, sizeof(line) , filehandle) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';
        if( strcmp (username , line) == 0)
        {
            printf("Username Already Taken! Try Again\n ");
            return createAccount();
        }
    }
    
    printf("Enter a Password\n");
    scanf("%s", pass1);
    printf("Re-enter the Password\n");
    scanf("%s", pass2);
    if(strcmp(pass1,pass2) != 0)
    {
        printf("Both Passwords DO NOT match!\nDo you want to try again?\n1. Yes\n2. No\n ");
        int userinput = validation(1,2);
        if(userinput == 1)
        {
            return createAccount();
        } 
        else
        {
            return 2;
        }
    }
    filehandle = fopen("LoginDetails.txt", "a");
    if(filehandle == NULL)
    {
        return 1;
    }
    fprintf(filehandle,"%s\n%s\n", username, pass1);
    fclose(filehandle);
    if(fetchdetails() == 1)
    {
        printf("File not Found!");
        return 1;
    }
    return 0;
}
// prints credits before ending the program
void end()
{
    system("cls");
    printf("Program Ending (3)");
    Sleep(300);
    system("cls");
    printf("Program Ending (2)");
    Sleep(300);
    system("cls");
    printf("Program Ending (1)");
    Sleep(300);
    system("cls");
    printf("Program Ending (0)");
    Sleep(300);
    system("cls");
    printf("\n\nThank You for using HR Management System created by:\n");
    printf("1. Aakif Abrar K24-0889\n2. Abdullah Omar K24-0532\n3. Rafay Ghouri K24-0728\n");
}
// displays all employees in a table. returns 0 if successfull, 1 if unsuccessfull or file not opened
int showemployees()
{
    system("cls");
    filehandle = fopen("EmployeeDetails.txt","r");
    if(filehandle == NULL)
    {
        return 1;
    }
    printf("#No.   Name                                 ID             Job Title                                Salary\n");
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
    char line[50];
    int num = 1;
    while(fgets(line, sizeof(line), filehandle))
    {
        printf(" %-6d",num);
        line[strcspn(line, "\n")] = '\0';
        printf("%-32s     ",line);
        fgets(line, sizeof(line), filehandle);
        line[strcspn(line, "\n")] = '\0';
        printf("%-10s     ",line);
        fgets(line, sizeof(line), filehandle);
        line[strcspn(line, "\n")] = '\0';
        printf("%-36s     ",line);
        fgets(line, sizeof(line), filehandle);
        line[strcspn(line, "\n")] = '\0';
        printf("%s\n",line);
        num++;
    }
    printf("\n\n");
    return 0;
}
// copies the login details from the file to the structure. returns 0 if successfull, 1 if unsuccessfull or file not opened
int fetchdetails()
{
    char line[50];
    filehandle = fopen("LoginDetails.txt","r");
    if(filehandle == NULL)
    {
        return 1;
    }
    else
    {
        int i = 0;
        while(fgets(line, sizeof(line), filehandle) != NULL) 
        {
            line[strcspn(line, "\n")] = '\0';
            strcpy(userdetails[i].username , line);
            fgets(line, sizeof(line), filehandle);
            line[strcspn(line, "\n")] = '\0';
            strcpy(userdetails[i].password , line);
            i++;
        }
        fclose(filehandle);
        return 0;
    }
}
// Validates input in a given range and keeps asking user for input until user enters a number in the range. Returns input.
int validation(int start, int end)
{
    int validation, userinput;
    validation = scanf("%d", &userinput);
    while(getchar()!='\n');
    while (validation == 0 || userinput > end || userinput < start)
    {
        printf("Invalid choice!\nEnter a number between %d and %d inclusively!\n",start,end);
        validation = scanf("%d", &userinput);
        while(getchar()!='\n');
    }
    return userinput;   
}
// shows options available for guests, returns one if user wants to go to the main menue
int guest()
{
    printf("\nOptions Available for Guests:\n\n");
    printf("1. Show All Employees\n");
    printf("2. Back\n");
    printf("3. Quit Program\n");
    int userinput = validation(1,3);
    if(userinput == 1)
    {
        if(showemployees() == 1)
        {
            printf("File not Found\n");
            return 1;
        }
        else
        {
            guest();
        }
    }
    else if(userinput == 2)
    {
        return 2;
    }
}
// Validates ID format and checks if ID exists in the file. if it does not exist then return 0, if it exists return 1. if file doesnt open then return 1.
int checkID(char ID[6])
{
    if( (ID[0] < '0' || ID[0] > '9') || (ID[1] < '0' || ID[1] > '9') || (ID[2] < '0' || ID[2] > '9') || (ID[3] < '0' || ID[3] > '9') )
    {
        printf("\nInvalid Format!!!!\n");
        return 2;
    }
    if(strlen(ID) > 4)
    {
        printf("Please write 4 digits only!\n");
        return 2;
    }
    filehandle = fopen("EmployeeDetails.txt", "r");
    if(filehandle == NULL)
    {
        return 1;
    }
    char line[50];
    while(fgets(line, sizeof(line), filehandle) != NULL)
    {
        fgets(line, sizeof(line), filehandle);
        line[strcspn(line, "\n")] = '\0';
        if(strcmp(line,ID) == 0)
        {
            printf("\nID Already Taken!! Enter a different ID\n");
            fclose(filehandle);
            return 2;
        }
    }

    fclose(filehandle);
    return 0;
}
