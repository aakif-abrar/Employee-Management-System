#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
FILE* filehandle;
// structure to store usernames and passwords.
struct users
{
    char username[50];
    char password[50];
};
// index 0 is aakif, index 1 is abdullah index 2 is rafay.
struct users userdetails[100];

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
// ask user for login details and verify from the file. returns 0 if successfull, 1 if file not opened and 2 if unsuccessfull
int login()
{
    char name[50], pass[50];
    int found = 0 , lineNumber, userinput;
    printf("Enter your username\n");
    scanf("%s", name);

    for(int i = 0 ; i<100 ; i++)
    {
        if(strcmp(userdetails[i].username, name) == 0)
        {
            found = 1;
            lineNumber = i;
            break;
        }
    }


    if(found == 1)
    {
        printf("Enter your password\n");
        scanf("%s", pass);
        if(strcmp(userdetails[lineNumber].password, pass)==0)
        {
            system("cls");
            printf("\nLogged in successfully!!\n\n");
            return 0;
        }
        else
        {
            printf("Incorrect Password!!\nDo you want to try again?\n1.Yes\n2.No\n");
            int userinput = validation(1,2);
            if(userinput == 1)
            {
                return login();
            }
            else
            {
                return 2;
            }
        }
    }
    else
    {
        printf("Username not found! Do you want to try again\n1.Yes\n2.No\n");
        userinput = validation(1,2);
        if(userinput == 1)
        {
            return login();
        }
        else
        {
            return 2;
        }
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
// asks user for employee ID and lets user edit that employee. returns 0 if successfull, 1 if file not opened, 2 if unsuccesssfull
int editemployee()
{
    filehandle = fopen("EmployeeDetails.txt", "r");
    FILE* tempfile = fopen("temp.txt","w");
    char line[50];
    if(filehandle==NULL || tempfile == NULL)
    {
        return 1;
    }
    char IDToChange[50], ID[50], name[50], title[50], newTitle[50];
    float salary,newSalary;
    printf("Enter the ID of the employee you want to edit\n");
    scanf("%s",IDToChange);
    getchar();
    int found = 0;
    while(fgets(name, sizeof(name), filehandle) != NULL)
    {
        name[strcspn(name, "\n")] = '\0';
        fgets(ID, sizeof(ID), filehandle);
        ID[strcspn(ID, "\n")] = '\0';
        fgets(title, sizeof(title), filehandle);
        title[strcspn(title, "\n")] = '\0';
        fgets(line, sizeof(line), filehandle);
        line[strcspn(line, "\n")] = '\0';
        salary = atof(line);
        if(strcmp(IDToChange , ID) == 0)
        {
            found = 1;
            printf("Enter the New Job Title\n");
            scanf("%[^\n]",newTitle);
            while (getchar() != '\n');
            capitalize(newTitle);
            printf("Enter the New Salary!\n");
            scanf("%f", &newSalary);
            getchar();
            fprintf(tempfile, "%s\n",name);
            fprintf(tempfile, "%s\n",ID);
            fprintf(tempfile, "%s\n",newTitle);
            fprintf(tempfile, "%.2f\n",newSalary);
        }
        else
        {
            fprintf(tempfile, "%s\n",name);
            fprintf(tempfile, "%s\n",ID);
            fprintf(tempfile, "%s\n",title);
            fprintf(tempfile, "%.2f\n",salary);
        }
    }
    fclose(filehandle);
    fclose(tempfile);
    if(found == 0)
    {
        printf("ID not found!\nDo you want to try again?\n1.Yes\n2.No\n");
        int userinput = validation(1,2);
        if(userinput == 1)
        {
            return editemployee();
        }
        else
        {
            return 2;
        }
    }
    else
    {
        filehandle = fopen("EmployeeDetails.txt","w");
        tempfile = fopen("temp.txt","r");
        if(filehandle==NULL || tempfile == NULL)
        {
            return 1;
        }
        while(fgets(line,sizeof(line), tempfile) != NULL)
        {
            fprintf(filehandle, "%s", line);
        }
        fclose(filehandle);
        fclose(tempfile);
        remove("temp.txt");
    }
    
    return 0;
}
// asks user for ID and delete that employee. returns 0 if successfull, 1 if  file not opened , 2 if unsuccessful
int delemployee()
{
    filehandle = fopen("EmployeeDetails.txt", "r");
    FILE* tempfile = fopen("temp.txt","w");
    char line[50];
    if(filehandle==NULL || tempfile == NULL)
    {
        return 1;
    }
    char IDToDelete[50], ID[50], name[50], title[50];
    float salary;
    printf("Enter the ID of the employee you want to Delete\n");
    scanf("%s",IDToDelete);
    getchar();
    int found = 0;
    while(fgets(name, sizeof(name), filehandle) != NULL)
    {
        name[strcspn(name, "\n")] = '\0';
        fgets(ID, sizeof(ID), filehandle);
        ID[strcspn(ID, "\n")] = '\0';
        fgets(title, sizeof(title), filehandle);
        title[strcspn(title, "\n")] = '\0';
        fgets(line, sizeof(line), filehandle);
        line[strcspn(line, "\n")] = '\0';
        salary = atof(line);
        if(strcmp(IDToDelete , ID) == 0)
        {
            found = 1;
        }
        else
        {
            fprintf(tempfile, "%s\n",name);
            fprintf(tempfile, "%s\n",ID);
            fprintf(tempfile, "%s\n",title);
            fprintf(tempfile, "%.2f\n",salary);
        }
    }
    fclose(filehandle);
    fclose(tempfile);
    if(found == 0)
    {
        printf("ID not found!\nDo you want to try again?\n1.Yes\n2.No\n");
        int userinput = validation(1,2);
        if(userinput == 1)
        {
            return delemployee();
        }
        else
        {
            return 2;
        }
    }
    else
    {
        filehandle = fopen("EmployeeDetails.txt","w");
        tempfile = fopen("temp.txt","r");
        if(filehandle==NULL || tempfile == NULL)
        {
            return 1;
        }
        while(fgets(line,sizeof(line), tempfile) != NULL)
        {
            fprintf(filehandle, "%s", line);
        }
        fclose(filehandle);
        fclose(tempfile);
        remove("temp.txt");
    }
    return 0;
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
// sorts data in the file based on Name( 'n' ) ID( 'i' ) or Salary( 's' ). returns 0 if successfull, 1 if unsuccessfull or file not opened
int Sort(char SortBasedOn)
{
    struct emp
    {
        char Name[50];
        char ID[50];
        char Title[50];
        float Salary;
    };


    filehandle = fopen("EmployeeDetails.txt","r");
    if(filehandle == NULL)
    {
        return 1;
    }
    char line[50];
    int count = 0;
    while(fgets(line,sizeof(line), filehandle) != NULL)
    {
        count ++;
    }
    fclose(filehandle);
    struct emp employees[(count/4)+1];

    printf("%d",count/4);
    filehandle = fopen("EmployeeDetails.txt","r");
    if(filehandle == NULL)
    {
        return 1;
    }
    for(int i = 0; i <count/4; i++)
    {
        fgets(line, sizeof(line), filehandle);
        line[strcspn(line , "\n")] = '\0';
        strcpy(employees[i].Name , line);

        fgets(line, sizeof(line), filehandle);
        line[strcspn(line , "\n")] = '\0';
        strcpy(employees[i].ID , line);
        
        fgets(line, sizeof(line), filehandle);
        line[strcspn(line , "\n")] = '\0';
        strcpy(employees[i].Title , line);
        
        fgets(line, sizeof(line), filehandle);
        line[strcspn(line , "\n")] = '\0';
        employees[i].Salary = atof(line);
    }

    fclose(filehandle);
    // using buble Sort
    struct emp temp;
    if(SortBasedOn == 'i')
    {
        for(int i = 0; i < count/4; i++)
        {
            for(int j = 0; j < (count/4) -1; j++)
            {
                if( atoi(employees[j].ID) > atoi(employees[j+1].ID) )
                {
                    temp = employees[j+1];
                    employees[j+1] = employees[j];
                    employees[j] = temp;   
                }
            }
        }
    }
    else if(SortBasedOn == 's')
    {
        for(int i = 0; i < count/4; i++)
        {
            for(int j = 0; j < (count/4) -1; j++)
            {
                if( employees[j].Salary > employees[j+1].Salary )
                {
                    temp = employees[j+1];
                    employees[j+1] = employees[j];
                    employees[j] = temp;   
                }
            }
        }
    }
    else if(SortBasedOn == 'n')
    {
        for(int i = 0; i < count/4; i++)
        {
            for(int j = 0; j < (count/4) -1; j++)
            {
                if( strcmp(employees[j].Name, employees[j+1].Name) > 0 )
                {
                    temp = employees[j+1];
                    employees[j+1] = employees[j];
                    employees[j] = temp;   
                }
            }
        }
    }



    filehandle = fopen("EmployeeDetails.txt", "w");
    for(int i = 0; i<count/4; i++)
    {
        fprintf(filehandle, "%s\n",employees[i].Name );
        fprintf(filehandle, "%s\n",employees[i].ID );
        fprintf(filehandle, "%s\n",employees[i].Title );
        fprintf(filehandle, "%.2f\n",employees[i].Salary);
    }
    fclose(filehandle);
    
    return 0;
}
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
// main menue after logged in as management, returns 0 if logout, returns 1 if file not found, returns 2 if quit
int loggedin()
{
    int userinput, createAccountValue, deletemployeeValue, editemployeeValue;
    printf("\nChoose from the following options\n");
    printf("1. Add a New Employee\n");
    printf("2. Edit Employee Details\n");
    printf("3. Show All Employees\n");
    printf("4. Delete an Employee\n");
    printf("5. Remove All Employees\n");
    printf("6. Add a New Account\n");
    printf("7. Log Out\n");
    printf("8. Quit Program\n");
    userinput = validation(1,8);
    switch (userinput)
    {
    case 1:
        if(addemploy() != 0)
        {
            printf("File not found!");
            return 1;
        }
        system("cls");
        printf("\nDetails Added Successfully!!!\n");
        Sleep(600);
        system("cls");
        return loggedin();
        break;
    case 2:
        showemployees();
        editemployeeValue = editemployee();
        if(editemployeeValue == 1)
        {
            printf("File not found!");
            return 1;
        }
        else if(editemployeeValue == 2)
        {
            system("cls");
            return loggedin();
        }
        Sleep(600);
        system("cls");
        printf("\nDetails Edited Successfully!\n\n");
        return loggedin();
        break;
    case 3:
        while(1)
        {
            if(showemployees() != 0)
            {
                printf("File not found!");
                return 1;
            }
            printf("Choose from the Following opetions:\n1. Sort with order of Name\n");
            printf("2. Sort with order of ID\n");
            printf("3. Sort with order of Salary\n");
            printf("4. Back\n\n");
            userinput = validation(1,4);
            switch(userinput)
            {
                case 1:
                    if(Sort('n') != 0)
                    {
                        printf("File not found");
                        return 1;
                    }
                    system("cls");
                    printf("Sorted Successfully!!");
                    Sleep(600);
                    break;
                
                case 2:
                    if(Sort('i') != 0)
                    {
                        printf("File not found");
                        return 1;
                    }
                    system("cls");
                    printf("Sorted Successfully!!");
                    Sleep(600);
                    break;
                
                case 3:
                    if(Sort('s') != 0)
                    {
                        printf("File not found");
                        return 1;
                    }
                    system("cls");
                    printf("Sorted Successfully!!");
                    Sleep(600);
                    break;
            }
            if(userinput == 4)
            {
                break;
            }
        }
        system("cls");
        return loggedin();
        break;
        
    case 4:
        showemployees();
        deletemployeeValue = delemployee();
        if(deletemployeeValue == 1)
        {
            printf("File Not Found!\n");
            return 1;
        }
        else if(deletemployeeValue == 2)
        {
            system("cls");
            return loggedin();
        }
        system("cls");
        printf("\nEmployee Deleted Successfully!\n\n");
        Sleep(600);
        system("cls");
        return loggedin();
        break;
    case 5:
        printf("Are you sure that you want to Delete All Employees???\n1. Yes\n2. No\n");
        userinput = validation(1,2);
        if(userinput == 1)
        {
            filehandle = fopen("EmployeeDetails.txt","w");
            fclose(filehandle);
            system("cls");
            printf("Factory Reset Done!\n");
            Sleep(600);
            system("cls");
        }
        return loggedin();
        
        break;
    case 6:
        system("cls");
        createAccountValue = createAccount();
        if(createAccountValue == 1)
        {
            printf("File Not Found!");
            return 1;
        }
        else if(createAccountValue == 2)
        {
            return loggedin();
        }
        else
        {
            system("cls");
            printf("Account Created Successfully!");
            Sleep(600);
            return loggedin();
        }
        break; 
    case 8:
        return 2;
        break;       
    }
    return 0;
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
// main function
int main()
{
    system("cls");
    int userinput;
    if(testfiles() == 1)
    {   
        printf("\nSome text files couldn't be found!\n\nDo you want to Create the Missing Files?\n1. Yes\n2. No\n");
        userinput = validation(1,2);
        if(userinput==1)
        {
            createfiles();
        }
        else
        {
            end();
            return 0;
        }
    }
    int filecheck = fetchdetails();
    if(filecheck==1)
    {
        printf("File not Found");
        return 0;
    }
    mainmenue();




    end();
    return 0;
}
