#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
    char customer[9];
    char customer_pin[5];
    int amountinbank;
    struct node *next;
}*head;


void insertFirst (char* cust, char* c_p, int a_i_b){
    struct node *link = (struct node*)malloc(sizeof(struct node));
    struct node *tmp = head;
    int i,j;
    for(j=0; j<=8;j++){
        link->customer[j]=cust[j];
    }
    for(i=0; i<=4; i++){
        link->customer_pin[i] = c_p[i];
    }
    link->amountinbank= a_i_b;
    if (head == NULL){
        head= link;
        link->next= NULL;
    }else{
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp-> next=link;
        link->next= NULL;
    }
}
void bringList(struct node*head,char* userinp,char* customer__pin, int *balance){
    struct node *ptr= head;
    int k;
    while (ptr!=NULL){
        if(strcmp(ptr->customer,userinp)==0){
            for(k=0;k<=5;k++){
                *(customer__pin+k) = ptr->customer_pin[k];
            }
            *balance = ptr->amountinbank;
            return;
        }else
            ptr= ptr->next;
    }
}
int main(void){
    int amount;
    int b;
    int value;
    char*deposit="Deposit";
    char*withdraw= "Withdraw";
    int d,w;
    char userinp[9];
    char transaction_type[10];
    char pin[3];
    int* balance= NULL;
    char cust[9];
    char c_p[5];
    int a_i_b;
    char customer__pin[5];
    FILE*fin = fopen("datain.txt","r");
    while(fscanf(fin,"%s %s ß%d", cust,c_p,&a_i_b)!=EOF){
        insertFirst(cust,c_p,a_i_b);
    }
    printf("Enter account number: ");
    scanf("%s",userinp);
    bringList(head,userinp,customer__pin,balance);
    printf("Please enter pin: ");
    scanf("%s",pin);
    b= *balance;
    int x= strcmp(pin,customer__pin);
    if (x==0){
        printf("Pin is correct\n");
        printf("Deposit or Withdraw?\n");
        scanf("%s",transaction_type);
        d= strcmp(transaction_type,deposit);
        w= strcmp(transaction_type,withdraw);
        if (w==0){
            printf("\n===== Your current balance is: $ %d =====", *balance);
            printf("\nHow much would you like to withdraw? \n");
            scanf("%d",&amount);
            value = b-amount;
            if(value>0){
                printf("Your transaction is being processed\n");
                b= b-amount;
                printf("==== Your balance is now: $%d =====\n",b);
            }else{
                printf("Your transaction cannot be processed\n");
                printf("Insufficient funds\n");}
            
            
        }else if(d==0){
            printf("\n===== Your current balance is: $ %d=====", b);
            printf("\nHow much would you like to deposit? \n");
            scanf("%d",&amount);
            printf("Your transaction is being processed\n");
            b= b+amount;
            printf("==== Your balance is now: $%d =====\n",b);
            
        }else{
            printf("That is not an option :( \n");
        }
    } else
        printf("Pin is incorrect\n");
    fclose(fin);
    return 0;
    
}





