#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "function.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int choice;
    do{
        printf("\n*** Welcome to Bank Account Management System ***\n");
        printf("[1] Admin\n");
        printf("[2] User\n");
        printf("[0] Exit\n");
        printf("Choose your role: ");
        
        int roleChoice;
        scanf("%d", &roleChoice);
        
        switch (roleChoice) {
            case 1: {
                int loggedIn = adminLogin();
                if (loggedIn) {
                    adminMenu();
                } else {
                    printf("Invalid admin credentials.\n");
                }
                break;
            }
            case 2: {
                char email[50], password[50];
                userLogin(email, password);
                userMenu();
                break;
            }
            case 0:
                printf("Exiting the program...\n");
                printf("========= Thank You =========\n");
                printf("========= See you soon ======\n");
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }while(choice != 0);

    return 0;
}
