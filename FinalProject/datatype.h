//noi cac em di import nhung thu vien, khai bao cac struct

#define MAX_USERS 100 //Tao mang toi da la 100 nguoi

typedef struct {
    char id[20];
    char name[50];
    char email[50];
    char phone[15];
    int gender; // 0: Male, 1: Female
    int day, month, year;
    char username[50];
    long long balance;
    int status; // 0: Locked, 1: Active
} User;

User users[MAX_USERS];
int userCount = 0;
