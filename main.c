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
	while(cikis==0){ // cikisi en baþta 0 olarak atadým eðer artýk yeni dosya açýlamazsa cikis 1 olacak ve while döngüsünden çýkacak
		itoa(i,filename,10); // i deðerini 1 atadým ve bunu karaktere çeviriyorum 
		strcat(filename,txt); // daha sonra ise sonuna .txt ekliyorum ve ilgili dosyanýn konuma gidiyorum 
		if((fs=fopen(filename,"r"))==NULL){ // eðer dosya açýlmazsa cikis 1 olacak
      		cikis=1;
  		}
  		else{
  			j=0; // j'yi dosyadaki karakterler için kullanýyorum 
			while(!feof(fs)){ // dosya sonuna kadar devam ediyor
			 	ch=fgetc(fs); // dosyadaki karakteri okuyup ch'ye atýyorum
			 	if(ch>='a' && ch<='z' || ch=='ç' || ch=='ð' || ch=='ý' || ch=='ö' || ch=='ü' || ch=='þ'){ // eðer ch a ile z arasýndaysa veya türkçe karakterlerden biriyse bu if e giriyor
			 		dosya[j]=ch; // dosya diye oluþturduðum dizide dökümaný istenilen þekilde kaydediyorum
			 		bosluk=0; // bosluk adýnda deðiþken oluþturdum eðer birden fazla boþluk gelirse bir tane sadece bir tane boþluðu dosyaya atýyorum
			 		j++; // j'yi arttýrdým çünkü artýk dökümandaki karakteri aldýk ve dosyaya kaydettiðimiz için artýk j'yi arttýrýyorum
				}
				else if(ch>='A' && ch<='Z' || ch=='Ç' || ch=='Ð' || ch=='Ý' || ch=='Ö' || ch=='Ü' || ch=='Þ'){ // eðer ch büyük harfse onu küçük düþürüyorum
					if(ch=='I'){ // ingilizce büyük I aslýnda i demek olduðu için bu sorguyu yapýyorum eðer I varsa dosyaya i olarak atýyorum
						dosya[j]='i';
						j++;
					}
					else{
		            	ch=ch+fark; // fark'ý en baþta tanýmladým a-A 'nin farkýný tutuyor
		            	dosya[j]=ch;
		            	bosluk=0;
		            	j++;
	            	}
	        	}
				else if(ch==' '){ // boþluðu kontrol ediyorum
					if(bosluk==0){ // eðer bosluk 0 ise bundan bir önceki karakterin boþluk olmadýðý anlamýna geliyor ve dosyaya yazdýrýyorum
						dosya[j]=ch;
						bosluk=1; // artýk boþluk karakterini yazdýrdýðým icin bosluk u 1 yaptým
						j++;
					}
				}
				else{
					bosluk=0; // eðer noktalama iþareti gelirse boþluðu yine 0 yapýyorum
				}							 	
	  		}
	  		dosya[j]='\0'; // dosyanýn sonuna geliyorum
	  		sayac=0; // dosyadaki shingle sayýsýný bulmak icin sayac deðiþkeni tutuyorum
	  		for(a=0;a<=j-k;a++){ // ilk karakterden baþlayýp sondan k ninci karaktere kadar devam ediyorum
				ilk=a; // ilk e a yý atýyorum çünkü o karakterden sonraki k karaktere kadar bakmam lazým ve bunu a ile yaparsam bu sefer for döngüsünü bozarým
	  		    sutun=0;// sutun burda shingle in kaçýncý karakterinde olduðunu tutuyor
	  		    for(b=0;b<k;b++){ //shingle ý oluþturuyorum
		  			shingle[sutun]=dosya[ilk];
		  			sutun++;
		  			ilk++;
	  			}
	  			shingle[sutun]='\0';
	  			sonuc=shingle_search(shingle_files,shingle,sayac); // shingle_files matrisinde ayný shingle dan var mý diye bakýyorum 
				if(sonuc==-1){ // eðer sonuc -1 ise ayný shingledan olmadýðýný anlýyorum
					strcpy(shingle_files[sayac],shingle); // yeni shingle ý shingle_files a ekliyorum
					sayac++; 
				}
	  			sonuc=shingle_search(shingles,shingle,satir); // shingles matrisinde ayný shingle dan var mý diye bakýyorum
				if(sonuc==-1){ // eðer sonuc -1 ise ayný shingledan olmadýðýný anlýyorum
					strcpy(shingles[satir],shingle); // yeni shingle ý shingles a ekliyorum
					mtr[satir][i-1]=1; // mtr matrisinde de o satýrý ve sutunu 1 yapýyorum
					satir++; // satýr benim toplam shingle sayýmý tutuyor
				}
				else{
					mtr[sonuc][i-1]=1; // eðer sonuç -1 deðilse o shingle dan vardýr ve sonucta o shingle ýn hangi satýrda olduðunu döndürüyor ve mtr de orayý 1 yapýyorum
				}	  			
	  		} 
			printf("%2d. dosyadaki shingle sayisi : %d\n",i,sayac);  // dosyadki shingle sayýsýný yazýyorum
	  		while(strcmp(shingle_files[b],"")!=0){
	  			strcpy(shingle_files[b],"");
			}	  		
		}
		fclose(fs);
		i++; // her dosya için i yi arttýrýyorum
   	}
   	
   	file_count=i-2; // toplam dosya saiyis
   	printf("Toplam Shingle Sayisi: %d\n",satir);
   
	jaccard(mtr,satir,file_count); // jaccard matrisini yazdýrýyorum
	
	for(i=0;i<100;i++){ // hash matrisinde tüm deðerleri 9999 yapýyorum
	   	for(j=0;j<file_count;j++){
	   		hash[i][j]=9999;
		}
	}
	
	sayac=0; // sayacý hash fonksiyonlarýnýn kaçýncsýnda olduðumu bilmek için tutuyorum
	while(sayac<100){ // 100 hash fonksiyonu olana kadar
	cikis=0; // çýkýþ a'yý random atadýðým için tutuyorum a yi random atarken ayný sayýdan birden çok kere olmasýný engellemek için
		while(cikis==0){
			var=0;
		    a=rand()%satir; // a ya random bir sayi atadým
			for(i=0;i<sayac;i++){ 
				if(a==random[i]){ // random dizisi tutuyorum burada a nýn daha önceki deðerlerini saklýyorum
					var=1; // eðer a daha önceki deðerlerinden biriyse var deðiþkenini 1 yapýyorum
				}
			}
			if(var==0){ // eðer var hala 0 ise a'nýn deðerinin daha önce kullanýlmadýðýný anlýyorum
				random[sayac]=a; // random dizisine þimdiki deðerini ekliyorum
				cikis=1; // artýk çýkýþý 1 yapýyorum
			}
		}
		for(i=1;i<satir;i++){ // her satir için fonksiyon ile deðerini buluyorum
			h=((a*i)+1)%satir;
			for(j=0;j<file_count;j++){ // mtr matrisindeki i.satýradaki deðerlere bakýyorum eðer 1 ise o satýr ve sutunu hash fonksiyonundaki deðerle karþýlaþtýrýyorum
				if(mtr[i][j]==1){ 
					if(hash[sayac][j]>h){ // eðer h deðeri daha kuçükse h deðerini yerine yerleþtiriyorum
						hash[sayac][j]=h;
					}
				}
			}
		}
		sayac++; 
	}
	
	signature_jaccard(hash,file_count);// signature matrisi yazdýrýyorum
		
	return 0;
}


int shingle_search(char shingles[10000][31],char shingle[31],int satir){
	int i=0;
	for(i=0;i<satir;i++){ // tüm satýrlarý karþýlaþtýrýyorum
		if(strcmp(shingles[i],shingle)==0){ // eðer ayný shingle varsa o satiri döndürüyorum
			return i;
		}
	}
	return -1; // eðer ayný shingle dan yoksa -1 döndürüyorum
}

void jaccard(int mtr[10000][30],int satir,int file_count){
	int i,j,s,sayac,toplam;
	float ortalama,**matris;
	
	matris=(float **)calloc(satir,sizeof(float*)); // matris için yer açýyorum
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
   				if(mtr[s][i]==1 && mtr[s][j]==1){ // her satirdaki deðerleri iki dosya için karþýlaþtýrýyorum eðer ikiside 1 ise sayac ve toplamý arttýrýyorum 
   					sayac++;
					toplam++;
   				}
				else if(mtr[s][i]==1 || mtr[s][j]==1){ // eðer sadece 1 i birse sadece toplamý arttýrýyorum
   					toplam++;
   				}     	
			}
			ortalama=(sayac*1.00)/toplam; // daha sonra o iki dosya için aralarýndaki benzerlik oranýný buluyorum
			matris[i][j]=ortalama;	
		}
	}
	printf("\n-------- Jackard Benzerligi ----------\n\n"); // matrisi yazdýrýyorum
	for(i=0;i<file_count+1;i++){
		if(i==0){
			printf("     ");
		}
		else{
		printf(" %2d |",i); // dosya isimlerini yazdýrýyorum
		}
	}
	printf("\n");
	
	for(i=0;i<file_count;i++){
		for(s=0;s<file_count+1;s++){
			printf("-----"); // her satirin arasýný kýsa çizgilerle ayýrýyorum
		}
		printf("\n%2d | ",i+1); // dosya ismini satýrýn baþýna yazdýrýyorum
	   	for(j=0;j<file_count;j++){
	   		printf("%.2f|",matris[i][j]); // dosyalarýn aralarýndaki benzerliði yazdýrýyorum
		}
		printf("\n");
	}
	
	for(i=0;i<satir;i++){ // matris için açtýðým alaný free ediyorum
		free(matris[i]);
	}
	free(matris);	
}
void signature_jaccard(int hash[100][30],int file_count){
	int i,j,s,sayac,toplam,cikis=0;
	float ortalama,**matris,esik;
	
	matris=(float **)calloc(100,sizeof(float*)); // matris için yer açýyorum
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
   			for(s=0;s<100;s++){ // her satir için iki dosyayi karþýlaþtýrýyorum eðer birbirlerine eþitlerse sayacý arttýrýyorum 
   				if(hash[s][i]==hash[s][j] && hash[s][i]!=9999){
   					sayac++;
   				}     	
			}
			ortalama=(sayac*1.00)/100; // daha sonra sayacý 100 e bölüyorum çünkü 100 fonksiyon var
			matris[i][j]=ortalama;		
		}
	}
	printf("\n\n-------- Min hashing Icin Imza Benzerlik Orani ----------\n\n"); // matrisi yazdýrýyorum
	for(i=0;i<file_count+1;i++){
		if(i==0){
			printf("     ");
		}
		else{
		printf(" %2d |",i); // dosya isimlerini yazdýrýyorum
		}
	}
	printf("\n");
	
	for(i=0;i<file_count;i++){
		for(s=0;s<file_count+1;s++){
			printf("-----"); // her satirin arasýný kýsa çizgilerle ayýrýyorum
		}
		printf("\n%2d | ",i+1); // dosya ismini satýrýn baþýna yazdýrýyorum
	   	for(j=0;j<file_count;j++){
	   		printf("%.2f|",matris[i][j]); // dosyalarýn aralarýndaki benzerliði yazdýrýyorum
		}
		printf("\n");
	}	
	
	while(cikis==0){

		printf("\n Esik degeri giriniz (0.1, 0.9 gibi float deger giriniz,cikis icin 1.0'dan yuksek deger giriniz) :"); // esik deðeri istiyorum
		scanf("%f",&esik);
		printf("\n");
		
		if(esik<=1.0){
		
			for(i=0;i<file_count+1;i++){
				if(i==0){
					printf("    ");
				}
				else{
				printf("%2d |",i); // dosya isimlerini yazdýrýyorum
				}
			}
			printf("\n");
			
			for(i=0;i<file_count;i++){ // tüm matrisi kontrol edip eþik deðerinden yüksek olan ikilileri buluyorun
				for(s=0;s<file_count+1;s++){
					printf("----"); // her satirin arasýný kýsa çizgilerle ayýrýyorum
				}
				printf("\n%2d |",i+1); // dosya ismini satýrýn baþýna yazdýrýyorum
				for(j=0;j<file_count;j++){
					if(matris[i][j]>=esik){
						printf(" 1 |"); // eðer esik deðerinden yüksekse 1 yazdýrýyorum
					}
					else{
						printf(" - |"); // deðilse - yazdýrýyorum
					}
				}
				printf("\n");
			}
		}
		else{
			cikis=1;
		}
	}
	
	for(i=0;i<100;i++){ // matris için açtýðým alaný free ediyorum
		free(matris[i]);
	}
	free(matris);
}
