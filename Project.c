#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_ACCOUNTS 100

struct Account{
    char accountId[20];    
    char fullName[50];
    char phone[15];
    double balance;
    int status;
};

struct Transaction{
    char tranId[20];
    char senderId[20];
    char receiverId[20];
    double amount;
    char type[10];
    char date[20];
};

int isNumber(char s[]) {
    for(int i = 0; s[i] != '\0' && s[i] != '\n'; i++){
        if(s[i] < '0' || s[i] > '9')
            return 0;
    }
    return 1;
}

int isLetter(char s[]) {
    for(int i = 0; s[i] != '\0'; i++){
        if(!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z') || s[i] == ' ')) {
            return 0;  
        }
    }
    return 1; 
}

void strToLower(char s[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = tolower((unsigned char)s[i]); 
    }
}


void create_new_account(struct Account accounts[], int i){
    if(i >= MAX_ACCOUNTS){
        printf("Tao tai khoan that bai!!!!");
        return;
    }
    
    snprintf(accounts[i].accountId, sizeof(accounts[i].accountId), "B25DTCN%03d", i + 1);
    printf("Ma tai khoan : %s\n", accounts[i].accountId);

    while(1){
        printf("Moi ban nhap ten: ");
        fgets(accounts[i].fullName, sizeof(accounts[i].fullName), stdin);
        accounts[i].fullName[strcspn(accounts[i].fullName, "\n")] = '\0';
        if(strlen(accounts[i].fullName) == 0){
            printf("Vui long nhap ten!\n");
    	}else if(!isLetter(accounts[i].fullName)){
    		printf("loi, vui long nhap lai!\n");
        }else{
        	break;
		} 
    }

    while(1){
    printf("Moi ban nhap so dien thoai: ");
    char temp[20];
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    
    if(strlen(temp) == 0){
        printf("Vui long nhap SDT!\n");
        continue;
    }
    
    if(!isNumber(temp)){
        printf("SDT khong hop le!\n");
        continue; 
    }

    int found = 0;
    for(int j = 0; j < i; j++){
        if(strcmp(accounts[j].phone, temp) == 0){
            found = 1;
            break;
        }
    }

    if(found){
        printf("SDT da ton tai, Vui long nhap lai.\n");
        continue; 
    }

    strcpy(accounts[i].phone, temp);
    break; 
}

    
    accounts[i].balance = 0.0;
    accounts[i].status  = 1;
    
    printf("Tao tai khoan thanh cong!!!\n");
}

void update_account(struct Account accounts[], int size){
    char searchId[20];
    int flag = -1;

    while(1){
        printf("Nhap ID tai khoan can cap nhat: ");
        fgets(searchId, sizeof(searchId), stdin);
        searchId[strcspn(searchId, "\n")] = '\0'; 

        if(strlen(searchId) == 0){
            printf("ID trong, vui long nhap lai!\n");
            continue;
        }

        flag = -1;
        for(int i = 0; i < size; i++){
            if(strcmp(accounts[i].accountId, searchId) == 0){
                flag = i;
                break;
            }
        }

        if(flag == -1){
            printf("Khong tim thay tai khoan, vui long nhap lai!\n");
        } else break;
    }

    printf("Cap nhat tai khoan: %s\n", accounts[flag].accountId);
    printf("Ten cu: %s\n", accounts[flag].fullName);
    printf("SDT cu: %s\n", accounts[flag].phone);

    while(1){
        char newName[50];
        printf("Cap nhat ten moi : ");
        fgets(newName, sizeof(newName), stdin);
        newName[strcspn(newName, "\n")] = '\0';

        if(strlen(newName) == 0){  
            break;
        } else if(!isLetter(newName)){
            printf("Loi, vui long nhap lai!\n");
        } else {
            strcpy(accounts[flag].fullName, newName);
            break;
        }
    }

    while(1){
        char newPhone[20];
        printf("Cap nhat SDT moi : ");
        fgets(newPhone, sizeof(newPhone), stdin);
        newPhone[strcspn(newPhone, "\n")] = '\0';

        if(strlen(newPhone) == 0){  
            break;
        }

        if(!isNumber(newPhone)){
            printf("lpi, vui long nhap lai!\n");
            continue;
        }

        int duplicate = 0;
        for(int i = 0; i < size; i++){
            if(i != flag && strcmp(accounts[i].phone, newPhone) == 0){
                duplicate = 1;
                break;
            }
        }

        if(duplicate){
            printf("SDT da ton tai, vui long nhap lai!\n");
        } else {
            strcpy(accounts[flag].phone, newPhone);
            break;
        }
    }

    printf("Cap nhat thanh cong!\n");
}


void lock_account(struct Account accounts[], int size){
    char searchId[20];
    char confirm;
    int found = -1;

    while (1) {
        printf("Nhap ID tai khoan can khoa: ");
        fgets(searchId, sizeof(searchId), stdin);
        searchId[strcspn(searchId, "\n")] = '\0';

        if(strlen(searchId) == 0){
            printf("ID khong duoc de trong! Vui long nhap lai.\n");
            continue;
        }

        found = -1;
        for (int i = 0; i < size; i++) {
            if (strcmp(accounts[i].accountId, searchId) == 0) {
                found = i;
                break;
            }
        }

        if (found == -1) {
            printf("Loi: Khong tim thay tai khoan! Vui long nhap lai.\n");
        } else {
            break; 
        }
    }

    if (accounts[found].status == 0) {
        printf("Loi: Tai khoan %s da bi khoa truoc do!\n", accounts[found].accountId);
        return;
    }

    while (1) {
        printf("Ban co chac chan muon khoa tai khoan %s khong? (Y/N): ",
               accounts[found].accountId);
        scanf(" %c", &confirm); 
        getchar();

        if (confirm == 'Y' || confirm == 'y') {
            accounts[found].status = 0;
            printf("Tai khoan %s da duoc khoa thanh cong!\n", accounts[found].accountId);
            break;
        }else if (confirm == 'N' || confirm == 'n') {
            printf("Da huy thao tac khoa tai khoan.\n");
            break;
        }else {
            printf("Lua chon khong hop le! Vui long nhap Y hoac N.\n");
        
   		}
    }
}

void search_account(struct Account accounts[], int size) {
    char keyword[50];
    int found = 0;

    printf("Nhap tu khoa tim kiem (ID hoac Ten): ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; 

    char lowerKeyword[50];
    strcpy(lowerKeyword, keyword);
    strToLower(lowerKeyword);

    printf("\n=== Ket qua tim kiem ===\n");

    for (int i = 0; i < size; i++) {
        char lowerName[50], lowerId[20];
        strcpy(lowerName, accounts[i].fullName);
        strToLower(lowerName);
        strcpy(lowerId, accounts[i].accountId);
        strToLower(lowerId);

        if (strstr(lowerId, lowerKeyword) != NULL || strstr(lowerName, lowerKeyword) != NULL) {
            printf("ID: %s | Ten: %s | Phone: %s | Balance: %.2f | Status: %s\n",
                   accounts[i].accountId,
                   accounts[i].fullName,
                   accounts[i].phone,
                   accounts[i].balance,
                   accounts[i].status ? "Active" : "Locked");
            found = 1;
        }
    }

    if (!found) {
        printf("Khong co ket qua phu hop!\n");
    }
}



int main(){    
    struct Account accounts[MAX_ACCOUNTS];
    int accountCount = 0;
    int choice;
    
    do{
        printf("==========Mini Banking System=========\n");
        printf("||     1. Them tai khoan moi        ||\n");
        printf("||     2. Cap nhat thong tin        ||\n");
        printf("||     3. Quan ly trang thai        ||\n");
        printf("||     4. Tra cuu tai khoan         ||\n");
        printf("||     5. Danh sach tai khoan       ||\n");
        printf("||     6. Sap xep danh sach         ||\n");
        printf("||     7. Giao dich chuyen khoan    ||\n");
        printf("||     8. Lich su giao dich         ||\n"); 
        printf("||     9. Thoat!!!                  ||\n");
        printf("======================================\n");

        while (1) {
            printf("Moi ban nhap chuc nang: ");
            if (scanf("%d", &choice) != 1) {  
                printf("Vui long nhap so!\n");
                while(getchar() != '\n');     
            } else if (choice < 1 || choice > 9) {
                printf("Chuc nang khong hop le, nhap lai.\n");
                while(getchar() != '\n');     
            } else {
                while(getchar() != '\n');     
                break;
            }
        }
        
        switch(choice){
            case 1 :
                create_new_account(accounts, accountCount);
                accountCount++;
                break;

            case 2 :
                update_account(accounts, accountCount);
                break;

            case 3 :
                lock_account(accounts, accountCount);
                break;

            case 4 : 
                search_account(accounts, accountCount);
                break;

            case 9 :
                printf("Thoat!!!\n");
                break;

            default : 
                printf("Vui long lua chon lai.\n");
                break;
        }
        
    }while(choice != 9);
    
    return 0;
}

