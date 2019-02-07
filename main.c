#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>

int shingle_search(char shingles[10000][31],char shingle[31],int satir);
void jaccard(int mtr[10000][30],int satir,int file_count);
void signature_jaccard(int hash[100][30],int file_count);

int main(){
	
	int k,i=1,j=0,file_count,mtr[10000][30],cikis=0,sayac,satir=0,sutun,fark='a'-'A',bosluk=0,a,b,sonuc,ilk,hash[100][30],h,var,random[100],cik=0;
	char filename[6],txt[4]=".txt",shingles[10000][31],shingle[31],ch,dosya[9999],shingle_files[5000][31];
	FILE *fs;
	srand(time(NULL));
	while(cik==0){
		printf("k-shingle icin k sayisini giriniz:");
		scanf("%d",&k);
		cik=1;
		if(k>=31 || k<2 ){
			printf("Lutfen 2-30 araliginda deger giriniz.\n");
			cik=0;
		}
	}
	while(cikis==0){ // cikisi en ba�ta 0 olarak atad�m e�er art�k yeni dosya a��lamazsa cikis 1 olacak ve while d�ng�s�nden ��kacak
		itoa(i,filename,10); // i de�erini 1 atad�m ve bunu karaktere �eviriyorum 
		strcat(filename,txt); // daha sonra ise sonuna .txt ekliyorum ve ilgili dosyan�n konuma gidiyorum 
		if((fs=fopen(filename,"r"))==NULL){ // e�er dosya a��lmazsa cikis 1 olacak
      		cikis=1;
  		}
  		else{
  			j=0; // j'yi dosyadaki karakterler i�in kullan�yorum 
			while(!feof(fs)){ // dosya sonuna kadar devam ediyor
			 	ch=fgetc(fs); // dosyadaki karakteri okuyup ch'ye at�yorum
			 	if(ch>='a' && ch<='z' || ch=='�' || ch=='�' || ch=='�' || ch=='�' || ch=='�' || ch=='�'){ // e�er ch a ile z aras�ndaysa veya t�rk�e karakterlerden biriyse bu if e giriyor
			 		dosya[j]=ch; // dosya diye olu�turdu�um dizide d�k�man� istenilen �ekilde kaydediyorum
			 		bosluk=0; // bosluk ad�nda de�i�ken olu�turdum e�er birden fazla bo�luk gelirse bir tane sadece bir tane bo�lu�u dosyaya at�yorum
			 		j++; // j'yi artt�rd�m ��nk� art�k d�k�mandaki karakteri ald�k ve dosyaya kaydetti�imiz i�in art�k j'yi artt�r�yorum
				}
				else if(ch>='A' && ch<='Z' || ch=='�' || ch=='�' || ch=='�' || ch=='�' || ch=='�' || ch=='�'){ // e�er ch b�y�k harfse onu k���k d���r�yorum
					if(ch=='I'){ // ingilizce b�y�k I asl�nda i demek oldu�u i�in bu sorguyu yap�yorum e�er I varsa dosyaya i olarak at�yorum
						dosya[j]='i';
						j++;
					}
					else{
		            	ch=ch+fark; // fark'� en ba�ta tan�mlad�m a-A 'nin fark�n� tutuyor
		            	dosya[j]=ch;
		            	bosluk=0;
		            	j++;
	            	}
	        	}
				else if(ch==' '){ // bo�lu�u kontrol ediyorum
					if(bosluk==0){ // e�er bosluk 0 ise bundan bir �nceki karakterin bo�luk olmad��� anlam�na geliyor ve dosyaya yazd�r�yorum
						dosya[j]=ch;
						bosluk=1; // art�k bo�luk karakterini yazd�rd���m icin bosluk u 1 yapt�m
						j++;
					}
				}
				else{
					bosluk=0; // e�er noktalama i�areti gelirse bo�lu�u yine 0 yap�yorum
				}							 	
	  		}
	  		dosya[j]='\0'; // dosyan�n sonuna geliyorum
	  		sayac=0; // dosyadaki shingle say�s�n� bulmak icin sayac de�i�keni tutuyorum
	  		for(a=0;a<=j-k;a++){ // ilk karakterden ba�lay�p sondan k ninci karaktere kadar devam ediyorum
				ilk=a; // ilk e a y� at�yorum ��nk� o karakterden sonraki k karaktere kadar bakmam laz�m ve bunu a ile yaparsam bu sefer for d�ng�s�n� bozar�m
	  		    sutun=0;// sutun burda shingle in ka��nc� karakterinde oldu�unu tutuyor
	  		    for(b=0;b<k;b++){ //shingle � olu�turuyorum
		  			shingle[sutun]=dosya[ilk];
		  			sutun++;
		  			ilk++;
	  			}
	  			shingle[sutun]='\0';
	  			sonuc=shingle_search(shingle_files,shingle,sayac); // shingle_files matrisinde ayn� shingle dan var m� diye bak�yorum 
				if(sonuc==-1){ // e�er sonuc -1 ise ayn� shingledan olmad���n� anl�yorum
					strcpy(shingle_files[sayac],shingle); // yeni shingle � shingle_files a ekliyorum
					sayac++; 
				}
	  			sonuc=shingle_search(shingles,shingle,satir); // shingles matrisinde ayn� shingle dan var m� diye bak�yorum
				if(sonuc==-1){ // e�er sonuc -1 ise ayn� shingledan olmad���n� anl�yorum
					strcpy(shingles[satir],shingle); // yeni shingle � shingles a ekliyorum
					mtr[satir][i-1]=1; // mtr matrisinde de o sat�r� ve sutunu 1 yap�yorum
					satir++; // sat�r benim toplam shingle say�m� tutuyor
				}
				else{
					mtr[sonuc][i-1]=1; // e�er sonu� -1 de�ilse o shingle dan vard�r ve sonucta o shingle �n hangi sat�rda oldu�unu d�nd�r�yor ve mtr de oray� 1 yap�yorum
				}	  			
	  		} 
			printf("%2d. dosyadaki shingle sayisi : %d\n",i,sayac);  // dosyadki shingle say�s�n� yaz�yorum
	  		while(strcmp(shingle_files[b],"")!=0){
	  			strcpy(shingle_files[b],"");
			}	  		
		}
		fclose(fs);
		i++; // her dosya i�in i yi artt�r�yorum
   	}
   	
   	file_count=i-2; // toplam dosya saiyis
   	printf("Toplam Shingle Sayisi: %d\n",satir);
   
	jaccard(mtr,satir,file_count); // jaccard matrisini yazd�r�yorum
	
	for(i=0;i<100;i++){ // hash matrisinde t�m de�erleri 9999 yap�yorum
	   	for(j=0;j<file_count;j++){
	   		hash[i][j]=9999;
		}
	}
	
	sayac=0; // sayac� hash fonksiyonlar�n�n ka��ncs�nda oldu�umu bilmek i�in tutuyorum
	while(sayac<100){ // 100 hash fonksiyonu olana kadar
	cikis=0; // ��k�� a'y� random atad���m i�in tutuyorum a yi random atarken ayn� say�dan birden �ok kere olmas�n� engellemek i�in
		while(cikis==0){
			var=0;
		    a=rand()%satir; // a ya random bir sayi atad�m
			for(i=0;i<sayac;i++){ 
				if(a==random[i]){ // random dizisi tutuyorum burada a n�n daha �nceki de�erlerini sakl�yorum
					var=1; // e�er a daha �nceki de�erlerinden biriyse var de�i�kenini 1 yap�yorum
				}
			}
			if(var==0){ // e�er var hala 0 ise a'n�n de�erinin daha �nce kullan�lmad���n� anl�yorum
				random[sayac]=a; // random dizisine �imdiki de�erini ekliyorum
				cikis=1; // art�k ��k��� 1 yap�yorum
			}
		}
		for(i=1;i<satir;i++){ // her satir i�in fonksiyon ile de�erini buluyorum
			h=((a*i)+1)%satir;
			for(j=0;j<file_count;j++){ // mtr matrisindeki i.sat�radaki de�erlere bak�yorum e�er 1 ise o sat�r ve sutunu hash fonksiyonundaki de�erle kar��la�t�r�yorum
				if(mtr[i][j]==1){ 
					if(hash[sayac][j]>h){ // e�er h de�eri daha ku��kse h de�erini yerine yerle�tiriyorum
						hash[sayac][j]=h;
					}
				}
			}
		}
		sayac++; 
	}
	
	signature_jaccard(hash,file_count);// signature matrisi yazd�r�yorum
		
	return 0;
}


int shingle_search(char shingles[10000][31],char shingle[31],int satir){
	int i=0;
	for(i=0;i<satir;i++){ // t�m sat�rlar� kar��la�t�r�yorum
		if(strcmp(shingles[i],shingle)==0){ // e�er ayn� shingle varsa o satiri d�nd�r�yorum
			return i;
		}
	}
	return -1; // e�er ayn� shingle dan yoksa -1 d�nd�r�yorum
}

void jaccard(int mtr[10000][30],int satir,int file_count){
	int i,j,s,sayac,toplam;
	float ortalama,**matris;
	
	matris=(float **)calloc(satir,sizeof(float*)); // matris i�in yer a��yorum
    if(matris==NULL){
		printf("Yetersiz bellek!");
	}
	for(i=0;i<satir;i++){
		matris[i]=(float *)calloc(file_count,sizeof(float));
		if(matris[i]==NULL){
			printf("Yetersiz bellek!");
		}
	}
	
	for(i=0;i<file_count;i++){ 
   		for(j=0;j<file_count;j++){
   			sayac=0;
   			toplam=0;
   			for(s=0;s<satir;s++){
   				if(mtr[s][i]==1 && mtr[s][j]==1){ // her satirdaki de�erleri iki dosya i�in kar��la�t�r�yorum e�er ikiside 1 ise sayac ve toplam� artt�r�yorum 
   					sayac++;
					toplam++;
   				}
				else if(mtr[s][i]==1 || mtr[s][j]==1){ // e�er sadece 1 i birse sadece toplam� artt�r�yorum
   					toplam++;
   				}     	
			}
			ortalama=(sayac*1.00)/toplam; // daha sonra o iki dosya i�in aralar�ndaki benzerlik oran�n� buluyorum
			matris[i][j]=ortalama;	
		}
	}
	printf("\n-------- Jackard Benzerligi ----------\n\n"); // matrisi yazd�r�yorum
	for(i=0;i<file_count+1;i++){
		if(i==0){
			printf("     ");
		}
		else{
		printf(" %2d |",i); // dosya isimlerini yazd�r�yorum
		}
	}
	printf("\n");
	
	for(i=0;i<file_count;i++){
		for(s=0;s<file_count+1;s++){
			printf("-----"); // her satirin aras�n� k�sa �izgilerle ay�r�yorum
		}
		printf("\n%2d | ",i+1); // dosya ismini sat�r�n ba��na yazd�r�yorum
	   	for(j=0;j<file_count;j++){
	   		printf("%.2f|",matris[i][j]); // dosyalar�n aralar�ndaki benzerli�i yazd�r�yorum
		}
		printf("\n");
	}
	
	for(i=0;i<satir;i++){ // matris i�in a�t���m alan� free ediyorum
		free(matris[i]);
	}
	free(matris);	
}
void signature_jaccard(int hash[100][30],int file_count){
	int i,j,s,sayac,toplam,cikis=0;
	float ortalama,**matris,esik;
	
	matris=(float **)calloc(100,sizeof(float*)); // matris i�in yer a��yorum
    if(matris==NULL){
		printf("Yetersiz bellek!");
	}
	for(i=0;i<100;i++){
		matris[i]=(float *)calloc(file_count,sizeof(float));
		if(matris[i]==NULL){
			printf("Yetersiz bellek!");
		}
	}
	
	for(i=0;i<file_count;i++){
   		for(j=0;j<file_count;j++){
   			sayac=0;
   			for(s=0;s<100;s++){ // her satir i�in iki dosyayi kar��la�t�r�yorum e�er birbirlerine e�itlerse sayac� artt�r�yorum 
   				if(hash[s][i]==hash[s][j] && hash[s][i]!=9999){
   					sayac++;
   				}     	
			}
			ortalama=(sayac*1.00)/100; // daha sonra sayac� 100 e b�l�yorum ��nk� 100 fonksiyon var
			matris[i][j]=ortalama;		
		}
	}
	printf("\n\n-------- Min hashing Icin Imza Benzerlik Orani ----------\n\n"); // matrisi yazd�r�yorum
	for(i=0;i<file_count+1;i++){
		if(i==0){
			printf("     ");
		}
		else{
		printf(" %2d |",i); // dosya isimlerini yazd�r�yorum
		}
	}
	printf("\n");
	
	for(i=0;i<file_count;i++){
		for(s=0;s<file_count+1;s++){
			printf("-----"); // her satirin aras�n� k�sa �izgilerle ay�r�yorum
		}
		printf("\n%2d | ",i+1); // dosya ismini sat�r�n ba��na yazd�r�yorum
	   	for(j=0;j<file_count;j++){
	   		printf("%.2f|",matris[i][j]); // dosyalar�n aralar�ndaki benzerli�i yazd�r�yorum
		}
		printf("\n");
	}	
	
	while(cikis==0){

		printf("\n Esik degeri giriniz (0.1, 0.9 gibi float deger giriniz,cikis icin 1.0'dan yuksek deger giriniz) :"); // esik de�eri istiyorum
		scanf("%f",&esik);
		printf("\n");
		
		if(esik<=1.0){
		
			for(i=0;i<file_count+1;i++){
				if(i==0){
					printf("    ");
				}
				else{
				printf("%2d |",i); // dosya isimlerini yazd�r�yorum
				}
			}
			printf("\n");
			
			for(i=0;i<file_count;i++){ // t�m matrisi kontrol edip e�ik de�erinden y�ksek olan ikilileri buluyorun
				for(s=0;s<file_count+1;s++){
					printf("----"); // her satirin aras�n� k�sa �izgilerle ay�r�yorum
				}
				printf("\n%2d |",i+1); // dosya ismini sat�r�n ba��na yazd�r�yorum
				for(j=0;j<file_count;j++){
					if(matris[i][j]>=esik){
						printf(" 1 |"); // e�er esik de�erinden y�ksekse 1 yazd�r�yorum
					}
					else{
						printf(" - |"); // de�ilse - yazd�r�yorum
					}
				}
				printf("\n");
			}
		}
		else{
			cikis=1;
		}
	}
	
	for(i=0;i<100;i++){ // matris i�in a�t���m alan� free ediyorum
		free(matris[i]);
	}
	free(matris);
}
