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
