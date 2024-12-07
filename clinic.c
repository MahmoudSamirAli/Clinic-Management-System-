/*********************************************/
/* Auther  : Mahmoud Samir Ali 		     */
/* Project : Clinic Managment System         */
/* Vesion  : v1.0                            */
/*********************************************/



#include <stdio.h>
#include <stdlib.h>

/* the patient node */
typedef struct Node
{
    char name[27]       ;
    char  age           ;
    char gender[8]      ;
    char Reserved_Slot  ; 
    int   id            ;

    struct Node * next ;
}data_t;
data_t* Head = NULL ;


int password = 1234 ; // default password 
char a1[][8] = {"2:30pm" , "3:00pm" , "3:30pm" , "4:00pm" , "4:30pm"} ; // eveyday avilable slots
char a2[5] = {1,1,1,1,1} ; // an array helped me display, arrange and rearrange slots.
char AvilableSlots = 5 ; //  an variable helped me display, arrange and rearrange slots.

/*Macros to avoid the magic numbers*/
#define Admin  1
#define User  2
#define AllSlots  5 
 
/*Reserve a specefic slot after displaying the avilavle ones */
void Admin_ReserveSlot (data_t *Temp )
{
    char ChooseSlot = 0 ; 
    char Counter1 = 1 , Counter2 = 0 ;

    printf("Avilable Slots : \n") ;
            
    for ( char i = 0 ; i < AllSlots ; i++)
    {
        if ( a2[i] == 0 )
            continue;
        printf("%d. %s\n",Counter1,a1[i]) ;
        Counter1++ ;  
    }

    printf("Enter the slot you choose : ") ;
    scanf("%d",&ChooseSlot) ; 

    /*Algorithm for rearrang slots*/
    for ( char i = 0 ; i < AllSlots ; i++)
    {
        if ( a2[i] == 0 )
            continue ;
        Counter2++ ; 
        if ( ChooseSlot == Counter2 )
        {
            Temp->Reserved_Slot = i ; //a1[i]
            a2[i] = 0 ;
        }    
    }

    AvilableSlots-- ;
    Counter1 = 1 ; 
}   


/*Check that the entered id is an unique one */
char CheckIDExistence (int ID)
{
    data_t * Temp = Head ; 
    char Repeatence = 0 ; 
    while ( 1 )
    {
        if (ID == Temp->id)
            Repeatence++ ; 
        if (Temp -> next == NULL)
            break ; 
        Temp = Temp->next ; 
    }
    return Repeatence ;  
}

/*Adding a new patien record to the system data base */
void Admin_AddNewRecord (void)
{
    char Check_ID = 0 ;

    data_t* Temp = NULL ; 

    if (AvilableSlots != 0 )
    {
        data_t *new = (data_t*) malloc(sizeof(data_t)) ;

        new->next = NULL ;

        /*Algorithm to add the node to the list dynamically*/
        if(Head != NULL) // the node created is not the first one
        {
            Temp = Head ; 

            while(Temp->next != NULL)
                    Temp = Temp->next ;
        
            Temp->next = new ; 
        }
        else // the not created is the first one
        {
            Head = new ;
        }

        printf("..Enter the patient data..\n") ;
        printf("Enter the patient name: ");
        scanf("%s",(new->name)) ; //scanf("%s",&(new->name)) ; wrong (scanf need address , name is address) 
        printf("Enter the patient age: ");
        scanf("%d",&(new->age)) ;
        printf("Enter the patient gender: ");
        scanf("%s",(new->gender)) ;
        for (char i = 0 ; i < 3 ; i++ ) 
        {
            printf("Enter the patient ID (only 4-digits): ");
            scanf("%d",&(new->id)) ;
            Check_ID = CheckIDExistence(new->id) ; 
            if ( Check_ID != 1 )
            {
                printf("---- sorry this ID is reserved ----\n") ;
                printf("---- you have - %d - more trails ----\n",(2-i)) ;
                if ( i == 2 )
                    printf("---- sorry you can't record these data with this id.----\n") ; 
                    return ;
            }
            else
            {     
                break ;
            }
        }
        Admin_ReserveSlot(new) ; 
        printf("=== The Patient Data Is Saved Sucssesfully. ===\nThank you\n") ;
    }
    else 
    {
        printf("*******************************************\n") ;
        printf("SORRY..!!\nThe clinic is complete today.\n")  ;
        printf("*******************************************\n") ;
    }
}

/*Editing an exist patien record inside the system data base */
void Admin_EditPatientRecord ( void )
{
    char Check_ID = 0 ;
    int A_id ; 
    data_t * Temp = Head ; 


    if (Head != NULL)
    {
        printf("Enter Patient ID : ") ; 
        scanf("%d",&A_id) ;
        /*Get patient node*/
        while( Temp -> id != A_id )
        {
            if (Temp->next == NULL && Temp->id != A_id)
            {
                printf("There is no patient with this id.\n") ; 
                return ; // go outside the whole function 
            }
            Temp = Temp -> next ; 
        }
    }
    else 
    {
        printf("There is no records yet.\n"); 
        return ; 
    }
    /* Show Patient Record*/
    printf("Patient Name   : %s\n",Temp->name);
    printf("Patient Age    : %d\n",Temp->age);
    printf("Patient Gender : %s\n",Temp->gender);
    printf("Patient ID     : %d\n",Temp->id);
    printf("Patient Slot     : %s\n",a1[Temp->Reserved_Slot]);

    /*Edit patient record*/
    printf("...Edit the patient record...\n");
    printf("Enter the patient name: ");
    scanf("%s",(Temp->name)) ; //scanf("%s",&(Temp->name)) ; wrong (scanf need address , name is address) 
    printf("Enter the patient age: ");
    scanf("%d",&(Temp->age)) ;
    printf("Enter the patient gender: ");
    scanf("%s",(Temp->gender)) ;
    for (char i = 0 ; i < 3 ; i++ ) 
    {
        printf("Enter the patient ID (only 4-digits): ");
        scanf("%d",&(Temp->id)) ;
        Check_ID = CheckIDExistence(Temp->id) ; 
        if ( Check_ID != 1 )
        {
            printf("---- sorry this ID is reserved ----\n") ;
            printf("---- you have - %d - more attempts ----\n",(2-i)) ;
            if ( i == 2 )
                printf("---- sorry you can't record these data with this id.----\n") ; 
        }
        else
        {    
            break ;
        }
    }
    /*make th slot free again before edit the already token*/
    a2[Temp->Reserved_Slot] = 1 ; 
    AvilableSlots++ ;

    Admin_ReserveSlot(Temp) ; 
    printf("=== The Patient Data Is Edited Sucssesfully. ===\nThank you\n") ; 

}

/*Displaying all data base*/
void Admin_ViewAllRecords (void)
{
    data_t* Temp = Head ; 
    if ( Head != NULL )
    {
        while(1)
        {
            if (Temp->next == NULL)
            {
                printf("-------------------------\n") ; 
                printf("Patient Name     : %s\n",Temp->name);
                printf("Patient Age      : %d\n",Temp->age);
                printf("Patient Gender   : %s\n",Temp->gender);
                printf("Patient ID       : %d\n",Temp->id);
                printf("Patient Slot     : %s\n",a1[Temp->Reserved_Slot]);
                break;
            }
            printf("-------------------------\n") ; 
            printf("Patient Name     : %s\n",Temp->name);
            printf("Patient Age      : %d\n",Temp->age);
            printf("Patient Gender   : %s\n",Temp->gender);
            printf("Patient ID       : %d\n",Temp->id);
            printf("Patient Slot     : %s\n",a1[Temp->Reserved_Slot]);

            Temp = Temp->next ;        
        }
    }
    else
    {
        printf("There is no records yet.\n") ; 
    }
}

/*Setting new admin password*/
void Admin_SetNewPassword (void)
{
    int l_pass ; 
    for (char i = 0 ; i < 3 ; i++ )
    {
        printf("Enter old password : ") ; 
        scanf("%d",&l_pass) ;
        if ( l_pass == password )
        {
            printf("Enter new password : ") ;
            scanf("%d",&password) ;  
            printf("The password has been updated sucssesfully.\n") ;
            break ;
        }  
        else
        {
            printf("The password you entered is wrong..\nTryagain\nYou have %d trails.\n", 2-i ) ;
            if (i==2)
                printf("Etla3 barrah ya 7aramay\n") ; 
        }
    }
}

/*Canceling a reservation*/
void Admin_CancelReservation (void)
{
    data_t * Temp1 , *Temp2 ;
    int id = 0 ;  
 
    if (Head != NULL)
    {
        printf("Enter patient id to cancel reservation : ") ;
        scanf("%d",&id) ;
        /*Check the id is right*/
        if ( CheckIDExistence(id) )
        {
            Temp2 = Head ; 
            while (1)
            {
                if (Temp2->id != id)
                {
                    Temp1 = Temp2 ; 
                    Temp2 = Temp2 -> next ; 
                }
                else
                {
                    break ; 
                }
            }
            if ( Temp2 != Head )
                Temp1->next = Temp2->next ; 
            else
            {
                Head = Temp2->next ;
            }
            /*make the slot free again*/
            a2[Temp2->Reserved_Slot] = 1 ; 
            AvilableSlots++ ;

            free(Temp2) ; 
            printf("---The reservation is canseled successfully---\n") ;
        }
        else
        {
            printf("There is no patient with this id.\n") ; 
        }
 
    }
    else 
    {
        printf("There is no records yet.\n"); 
        return ; 
    }
}

/*Check that the entered password is correct*/
char Admin_CheckAdminPassword (void)
{
    int l_pass ; 
    for (char i = 0 ; i < 3 ; i++ )
    {
        printf("Enter the password : ");
        scanf("%d",&l_pass) ;
        if (l_pass != password)
        {
            printf("Wrong password\n");
            printf("Note: you have %d other trails.\n",2-i) ; 
            if (i==2)
            {
                printf("Etla3 barrah ya 7aramay\n") ; 
                return 0 ;
            }
        }
        else
            return 1 ;  
    }
}

/*view a patient recored*/
void User_ViewRecord (void)
{
    data_t* Temp = Head ; 
    int L_id ; 

    if (Head == NULL )
    {
        printf("There is no records yet\n") ; 
        return ; 
    }
    printf("Enter Patient ID : ") ; 
    scanf("%d",&L_id) ; 
    if ( CheckIDExistence(L_id) == 1 )
    {
        while ( 1 )
        {
            if (Temp->id == L_id)
            {
                printf("Patient Name     : %s\n",Temp->name);
                printf("Patient Age      : %d\n",Temp->age);
                printf("Patient Gender   : %s\n",Temp->gender);
                printf("Patient ID       : %d\n",Temp->id);
                printf("Patient Slot     : %s\n",a1[Temp->Reserved_Slot]);
                break ; 
            }
            else 
                Temp = Temp->next ;
            
        }
    }
    else
    {
        printf("Wrong patient ID.\n") ; 
    }
}

/*view the avilable slots*/
void User_ViewAvilableSlots (void)
{
    char counter = 1 ; 
    if ( AvilableSlots != 0 )
    {
        for (char i = 0 ; i< AllSlots ; i++ )
        {
            if ( a2[i] == 0 )
            continue;
            printf("%d. %s\n",counter,a1[i]) ; 
            counter++;
        }
    }
    else
    {
        printf("*******************************************\n") ;
        printf("SORRY..!!\nThe clinic is complete today.\n")  ;
        printf("*******************************************\n") ;
    }
}

/*main function*/
int main (void)
{
    char Mode ;
    char ChooseAction = 0 ; 
    char ContStop = 0 ; 

    printf(".....Welcome.....\n");
    
    while (1)
    {
		/*Home Window*/
        printf("=====================================\n") ; 
		printf("=============== HOME  ===============\n") ; 
        printf("Choose the mode :\n1- Admin\n2- User\n3- Close the system\n") ; 
        printf("=====================================\n") ; 
        printf("Mode: ") ; 
        scanf ("%d",&Mode) ; 
        if (Mode == Admin)
        {
			/*Admin Window*/
            /*check password if right go ahead if not close the sys*/
            if ( Admin_CheckAdminPassword() != 0 )
            {
                /*public variable, confirm it's 0 for right sequence*/
                ChooseAction = 0 ;  
                while (1)
                {
                    printf("=====================================\n") ; 
                    printf("=========== Admin Window ============\n") ; 
                    printf("1. Add new patient record.\n") ;
                    printf("2. Edit patient record.\n") ;
                    printf("3. Cancel reservation.\n") ;
                    printf("4. Change the admin password.\n") ;
                    printf("5. View all records.\n") ; 
                    printf("6. back to HOME.\n") ; 
                    printf("=====================================\n") ; 
                    printf("Choose action : ") ; 
                    scanf("%d",&ChooseAction) ;
                    if (ChooseAction == 1 )
                    {
                        /*public variable, confirm it's 0 for right sequence*/
                        ContStop = 0 ; 
                        do
                        {
                            Admin_AddNewRecord() ; 
                            printf("1- Add another\n2- Close\n") ;
                            printf("Choose Action : ") ;
                            scanf("%d",&ContStop) ; 
                        } while (ContStop == 1 );
                    }
                    else if ( ChooseAction == 2 )
                    {
                        /*public variable, confirm it's 0 for right sequence*/
                        ContStop = 0 ; 
                        do
                        {
                            Admin_EditPatientRecord() ;
                            if (Head != NULL)
                            {
                                printf("1- Edit another\n2- Close\n") ;
                                printf("Choose Action : ") ;
                                scanf("%d",&ContStop) ; 
                            }
                        } while (ContStop == 1 );
                    }
                    else if ( ChooseAction == 3 )
                    {
                        ContStop = 0 ; 
                        do
                        {
                            Admin_CancelReservation() ;
                            if (Head != NULL)
                            {
                                printf("1- Cancel another\n2- Close\n") ;
                                printf("Choose Action : ") ;
                                scanf("%d",&ContStop) ; 
                            }
                        } while (ContStop == 1 );
                    }
                    else if ( ChooseAction == 4 )
                    {
                        Admin_SetNewPassword() ;
                    }
                    else if ( ChooseAction == 5 )
                    {
                        Admin_ViewAllRecords() ;
                    }
                    else if ( ChooseAction == 6 )
                    {
                        break ; 
                    }
                    else {/*Do Nothing*/}
                }
            }
            else
            {
                printf("The System Closed.\n") ; 
                return 0 ;
            }
        } 
        else if ( Mode == User)
        {
			/*USER window*/
            /*public variable, confirm it's 0 for right sequence*/
            ChooseAction = 0 ;  
            while (1)
            {
                printf("=====================================\n") ; 
                printf("=========== User Window ============\n") ; 
                printf("1. View patient record.\n") ;
                printf("2. View today's avilable slots.\n") ; 
                printf("3. back to HOME\n") ; 
                printf("=====================================\n") ; 
                printf("Choose Action : ") ; 
                scanf("%d",&ChooseAction) ; 
                if (ChooseAction == 1 )
                {
                    User_ViewRecord() ;
                }
                else if ( ChooseAction == 2  )
                {
                    User_ViewAvilableSlots() ;
                }
                else if ( ChooseAction == 3 )
                {
                    break;
                }
            } 
        }
        else
        {
           printf("The System Closed.\nGOOD BYE.") ;
           break ; 
        }
    }

     
}
