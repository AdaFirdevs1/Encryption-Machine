#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH 100

int main(){
	int choice, count;
	char key[27];
	char plain_text[MAX_TEXT_LENGTH];
    char cipher_text[MAX_TEXT_LENGTH];
	int key_set = 0;  // �ifre karakterlerinin ayarlan�p ayarlanmad���n� kontrol etmek i�in
	
	
	
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
            scanf("%26s", key); //bo�luksuz girilmesi gerekiyor
            
            int is_valid = 1; //hata kontrolleri buradan yap�lacak
            
            // ge�erli karakteri kontrol et
            if (strlen(key) != 26) {
                printf("ERROR: Key must contain 26 characters.\n\n");
                is_valid = 0;
                goto get_key_again1; //main men�ye d�nmesini engeller. anahtar� tekrar ister
                //continue;		//bunu kulland���m zaman men�ye geri at�yor fakat anahtar� tekrar istemesi gerek.
                
            } else {
                int counts[26] = {0};
                for (int i = 0; i < 26; i++) { //girilen karakterlerin i�inde gez
                    if (!isalpha(key[i])) { //alfabeden karakter girilmediyse ge�erli de�il.
                        printf("ERROR: Key must contain only alphabetic characters.\n\n");
                        is_valid = 0;
                        goto get_key_again2;
                		
                    }
                    
                    int index = toupper(key[i]) - 'A'; //alfabetik karakterleri b�y�k harfe d�nd�r ve 0-25 aras� say�larla belirt
                    counts[index]++; //bir harfin ka� kez kullan�ld���n� kontrol et
                    if (counts[index] > 1) { //birden �ok kez kullan�ld�ysa ge�ersiz.
                        printf("ERROR: Key must not contain repeated characters.\n\n");
                		is_valid = 0;
                		goto get_key_again3;
                        
                    }
                }
            }
			
			
            if (is_valid) { //e�er girilen anahtar ge�erliyse; is_valid = 1 ise
            	key_set = 1;
                printf("Key successfully set.\n\n"); //anlayabilmek i�in yazd�r�yorum
            }
            
            
        } else if (choice == 2) {
            
            if (!key_set) { //ilk se�imin 1 olmas�n� sa�lar.
                printf("ERROR: Please enter the key first.\n\n");
                continue;
            }
        	        	
			printf("Enter a plain text (max %d characters): ", MAX_TEXT_LENGTH); //en fazla 100 karakter girebilir.
            scanf(" %[^\n]s", plain_text); //bo�luklar� da dahil ederek max 100 karakter al�r
            
            //�ifreleme k�sm� 
			int plain_text_length = strlen(plain_text); //girilen d�z yaz�n�n uzunlu�unu al
					
            for (int i = 0; i < plain_text_length; i++) {
                
				if (isupper(plain_text[i])) { //b�y�k harfse
                    cipher_text[i] = toupper(key[plain_text[i] - 'A']); //0dan itibaren ka��nc� oldu�una bul
                    //"key[plain_text[i] - 'A']" k�sm�nda keye kar��l�k gelen de�eri al�n�r
                    
                } else if(islower(plain_text[i])) { // k���k harfse
                    cipher_text[i] = tolower(key[plain_text[i] - 'a']); //b�y�k harfle ayn�
                    
                } else { //alfabetik karakter de�ilse de�i�meden kal�r
                    cipher_text[i] = plain_text[i];
                }
            }
            
            printf("The cipher text is: %s\n\n", cipher_text); //�ifrelenmi� metni yaz
            
            
        } else if (choice == 3) {
        	
			if (!key_set) { //ilk se�imin 1 olmas�n� sa�lar.
                printf("ERROR: Please enter the key first.\n\n");
                continue;
            }
            
        	
        	printf("Enter a cipher text (max %d characters): ", MAX_TEXT_LENGTH);
            scanf(" %[^\n]s", cipher_text); //yine max 100 karakter al
            
            //�ifreyi ��zme k�sm�
            int cipher_text_length = strlen(cipher_text);

            for (int i = 0; i < cipher_text_length; i++) { //chipherdaki t�m karakterleri dola��r
            	
                if (isupper(cipher_text[i])) { //b�y�k harfse
                
                    for (int j = 0; j < 26; j++) { //keydeki t�m karakterleri dola��r
                        
						if (toupper(key[j]) == cipher_text[i]) { //e�er e�itse key dizisindeki j.inci karakterin �ifrelenmi� hali oldu�u anlam�na gelir
                            plain_text[i] = 'A' + j; //ger�ek b�y�k harf de�erini verir
                            break;
                        }
                    }
                } else if (islower(cipher_text[i])) { //k���k harfse
                
                    for (int j = 0; j < 26; j++) {
                    	
                        if (tolower(key[j]) == cipher_text[i]) {//e�er e�itse bu key dizisindeki j.inci karakterin �ifrelenmi� hali oldu�u anlam�na gelir
                            plain_text[i] = 'a' + j; //ger�ek k���k harf de�erini verir
                            break;
                        }
                    }
                } else { //e�er alfabetik de�ilse oldu�u gibi kal�r
                    plain_text[i] = cipher_text[i];
                }
            }
            plain_text[cipher_text_length] = '\0'; //sonuna bo� karakter ekle
            
            //normal yaz�
            printf("The plain text is: %s\n\n", plain_text);
            
            //��k��
        } else if (choice == 4) {
            printf("Exiting the program...\n\n");
        } else { //yanl�� se�im
            printf("Invalid choice. Please try again.\n\n");
        }
    } while (choice != 4);

    return 0;
}




