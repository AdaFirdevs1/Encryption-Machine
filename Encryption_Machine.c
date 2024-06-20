#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH 100

int main(){
	int choice, count;
	char key[27];
	char plain_text[MAX_TEXT_LENGTH];
    char cipher_text[MAX_TEXT_LENGTH];
	int key_set = 0;  // þifre karakterlerinin ayarlanýp ayarlanmadýðýný kontrol etmek için
	
	
	
	do{
		printf("****** MAIN MENU ******\n");
		printf("[1] Enter key\n");
		printf("[2] Encrypt message\n");
		printf("[3] Decrypt message\n");
		printf("[4] Exit\n");
		
		printf("Enter your choice: ");
		scanf("%d", &choice);
		
		
		
		if (choice == 1) {
		    get_key_again1:
		    get_key_again2:
		    get_key_again3:
            printf("Please enter the key: ");
            scanf("%26s", key); //boþluksuz girilmesi gerekiyor
            
            int is_valid = 1; //hata kontrolleri buradan yapýlacak
            
            // geçerli karakteri kontrol et
            if (strlen(key) != 26) {
                printf("ERROR: Key must contain 26 characters.\n\n");
                is_valid = 0;
                goto get_key_again1; //main menüye dönmesini engeller. anahtarý tekrar ister
                //continue;		//bunu kullandýðým zaman menüye geri atýyor fakat anahtarý tekrar istemesi gerek.
                
            } else {
                int counts[26] = {0};
                for (int i = 0; i < 26; i++) { //girilen karakterlerin içinde gez
                    if (!isalpha(key[i])) { //alfabeden karakter girilmediyse geçerli deðil.
                        printf("ERROR: Key must contain only alphabetic characters.\n\n");
                        is_valid = 0;
                        goto get_key_again2;
                		
                    }
                    
                    int index = toupper(key[i]) - 'A'; //alfabetik karakterleri büyük harfe döndür ve 0-25 arasý sayýlarla belirt
                    counts[index]++; //bir harfin kaç kez kullanýldýðýný kontrol et
                    if (counts[index] > 1) { //birden çok kez kullanýldýysa geçersiz.
                        printf("ERROR: Key must not contain repeated characters.\n\n");
                		is_valid = 0;
                		goto get_key_again3;
                        
                    }
                }
            }
			
			
            if (is_valid) { //eðer girilen anahtar geçerliyse; is_valid = 1 ise
            	key_set = 1;
                printf("Key successfully set.\n\n"); //anlayabilmek için yazdýrýyorum
            }
            
            
        } else if (choice == 2) {
            
            if (!key_set) { //ilk seçimin 1 olmasýný saðlar.
                printf("ERROR: Please enter the key first.\n\n");
                continue;
            }
        	        	
			printf("Enter a plain text (max %d characters): ", MAX_TEXT_LENGTH); //en fazla 100 karakter girebilir.
            scanf(" %[^\n]s", plain_text); //boþluklarý da dahil ederek max 100 karakter alýr
            
            //þifreleme kýsmý 
			int plain_text_length = strlen(plain_text); //girilen düz yazýnýn uzunluðunu al
					
            for (int i = 0; i < plain_text_length; i++) {
                
				if (isupper(plain_text[i])) { //büyük harfse
                    cipher_text[i] = toupper(key[plain_text[i] - 'A']); //0dan itibaren kaçýncý olduðuna bul
                    //"key[plain_text[i] - 'A']" kýsmýnda keye karþýlýk gelen deðeri alýnýr
                    
                } else if(islower(plain_text[i])) { // küçük harfse
                    cipher_text[i] = tolower(key[plain_text[i] - 'a']); //büyük harfle ayný
                    
                } else { //alfabetik karakter deðilse deðiþmeden kalýr
                    cipher_text[i] = plain_text[i];
                }
            }
            
            printf("The cipher text is: %s\n\n", cipher_text); //þifrelenmiþ metni yaz
            
            
        } else if (choice == 3) {
        	
			if (!key_set) { //ilk seçimin 1 olmasýný saðlar.
                printf("ERROR: Please enter the key first.\n\n");
                continue;
            }
            
        	
        	printf("Enter a cipher text (max %d characters): ", MAX_TEXT_LENGTH);
            scanf(" %[^\n]s", cipher_text); //yine max 100 karakter al
            
            //þifreyi çözme kýsmý
            int cipher_text_length = strlen(cipher_text);

            for (int i = 0; i < cipher_text_length; i++) { //chipherdaki tüm karakterleri dolaþýr
            	
                if (isupper(cipher_text[i])) { //büyük harfse
                
                    for (int j = 0; j < 26; j++) { //keydeki tüm karakterleri dolaþýr
                        
						if (toupper(key[j]) == cipher_text[i]) { //eðer eþitse key dizisindeki j.inci karakterin þifrelenmiþ hali olduðu anlamýna gelir
                            plain_text[i] = 'A' + j; //gerçek büyük harf deðerini verir
                            break;
                        }
                    }
                } else if (islower(cipher_text[i])) { //küçük harfse
                
                    for (int j = 0; j < 26; j++) {
                    	
                        if (tolower(key[j]) == cipher_text[i]) {//eðer eþitse bu key dizisindeki j.inci karakterin þifrelenmiþ hali olduðu anlamýna gelir
                            plain_text[i] = 'a' + j; //gerçek küçük harf deðerini verir
                            break;
                        }
                    }
                } else { //eðer alfabetik deðilse olduðu gibi kalýr
                    plain_text[i] = cipher_text[i];
                }
            }
            plain_text[cipher_text_length] = '\0'; //sonuna boþ karakter ekle
            
            //normal yazý
            printf("The plain text is: %s\n\n", plain_text);
            
            //çýkýþ
        } else if (choice == 4) {
            printf("Exiting the program...\n\n");
        } else { //yanlýþ seçim
            printf("Invalid choice. Please try again.\n\n");
        }
    } while (choice != 4);

    return 0;
}




