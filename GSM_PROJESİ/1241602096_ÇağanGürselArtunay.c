

#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"veri_seti.h"
#include<stdio.h>
#include<locale.h>


int mevcut_abone = 100;

// Aşağıda gerekli fonksiyonlarımı tanımladım.

void abone_ekle();
void abone_sil();
void abone_ara();
void abone_guncel();
void rapor_sadakat();
void rapor_tarih_degis();
void rapor_kampanya_siralama();

int main(){
    setlocale(LC_ALL,"turkish");
    int secim;
    int calisma_butonum = 1; // Döngü kontrolünü nesne ile yaptım.

    while(calisma_butonum){
        printf("=== GSM ABONE SİSTEMİ ===\n");
        printf("Güncel abonen => %d",mevcut_abone);
        printf("\n1. Yeni Abone Ekle\n");
        printf("2.Abone Sil\n");
        printf("3.Abone Bilgileri Güncelleme\n");
        printf("4.Abone Arama\n");
        printf("------------------------------\n");
        printf("5.Tarih Aralığına Göre Operatör Değişimi Raporu\n");
        printf("6.Operatöre ne kadar sadık analizi\n");
        printf("7.Kampanya popülerliği analizi\n");
        printf("0.Çıkış tuşu\n");

        printf("Lütfen seçim yapınız => "); scanf("%d",&secim);

        // Menü içerisinde seçtiği seçeneğe bağlı olarak yönlendireceğim.

        switch(secim) {
            case 1:
                abone_ekle();
                break;
            case 2:
                abone_sil();
                break;
            case 3:
                abone_guncel();
                break;
            case 4:
                abone_ara();
                break;
            case 5:
                rapor_tarih_degis();
                break;
            case 6:
                rapor_sadakat();
                break;
            case 7:
                rapor_kampanya_siralama();
                break;
            case 0:
                printf("Sistemden cikis yapiliyor. Iyi gunler...\n");
                calisma_butonum = 0; // While döngümü kırmak için 0 yaparım.
                break;
            default:
                printf("Hatali bir secim yaptiniz! Lutfen 0-7 arasi bir sayi girin.\n");
                break;
        }

    }
    return 0;

}

void abone_ekle(){
    // İlk adım olarak abone sayım sınırda mı kontrol ederim.
    if (mevcut_abone >= 1000) {
        printf("Hata: Hafıza dolu daha fazla ekleyemezsin !\n");
        return;
    }

    int i = mevcut_abone; // Daha rahat bir kullanım olması adına mevcut abone sayımı i değişkenine atarım.
    
    // Aşağıda tüm girdileri kontrol etmek adına birkaç değişken belirledim.
    int veri_dogru_mu = 0; // Döngü kontrolü için kullanacağım
    int k, hata_var;       // For döngülerinde sayac için k ve hata aldığımda bayrak mantığında kullanmak için hata_var değişkeni ayarladım.
    char gecici_buffer;    // klayve temizliği için belirledim çünkü eğer bu kontrolu yapmazsam taşmalar olabilir.
    char gecici_yazi[100]; // İlk girdiyi bu değişkende kontrol ettikden sonra listeye ekleyeceğim.

    printf("\n-- YENI ABONE KAYIT --\n");

    // Adım 1 Tc kimlik kontrolü.
    veri_dogru_mu = 0;
    while(veri_dogru_mu == 0) {
        hata_var = 0;
        printf("TC Kimlik No (11 Haneli olması gerekli): ");
        scanf("%s", gecici_yazi); 

        // Enter tuşu veya fazla karakterler için ilk başta buffer temizliyoruz.
        while ((gecici_buffer = getchar()) != '\n' && gecici_buffer != EOF);

        // Girilen tc ' nin uzunluğunu kontrol ediyorum.
        if(strlen(gecici_yazi) != 11) {
            printf("HATA: TC Kimlik No tam 11 haneli olmalıdır !!!!!\n");
            hata_var = 1;
        }

        // Negatif işaret veya harf girilmemesi için kontrol ediyorum.
        if(hata_var == 0) {
            for(k = 0; k < strlen(gecici_yazi); k++) {
                if(!isdigit(gecici_yazi[k])) {
                    printf("HATA: TC sadece rakamlardan oluşmalıdır (Harf, boşluk veya işaret olamaz)!\n");
                    hata_var = 1;
                    break;
                }
            }
        }

        // Son olarak doğrulugunu dogruladıktan sonra atama yapıp geçiyorum.
        if(hata_var == 0) {
            strcpy(kisiler[i].tc_no, gecici_yazi);
            veri_dogru_mu = 1; 
            // Degisken degerini 1 yaptıkdan sonra otomatık olarak donguden cıkıyorum.
        }
    }

    
    // ADIM 2 İsim Kontrolü.
    
    veri_dogru_mu = 0;
    while(veri_dogru_mu == 0) {
        hata_var = 0;
        printf("İsim: ");
        scanf("%s", gecici_yazi);
        
        // Enter tuşu veya fazla karakterler için ilk başta buffer temizliyoruz.
        while ((gecici_buffer = getchar()) != '\n' && gecici_buffer != EOF);

        // Girilen ismin uzunluğunu kontrol ediyorum.
        if(strlen(gecici_yazi) > 19) {
            printf("HATA: İsim çok uzun. Maksimum 19 karakter olabilir !!!!!\n");
            hata_var = 1;
        }

        if(hata_var == 0) {
            for(k = 0; k < strlen(gecici_yazi); k++) {
                /*Turkce karakterler (ı, ğ, ş vb.) gibi degerler genelde 0 'dan kucuk gorunuyor.
                 Bu yuzden sadece (int)gecici_yazi[k] > 0 diyerek standart karakterleri kontrol ediyoruz.
                 Aslında sayı veya sembolse kontrolu yapıyorum. Bunu yapmamın nedeni girdide ı harfini kullandığımda yanlış algılaması.Ben de ı harfinin negatif anlaşılmasını bu yönde kullanıyorum.
                 Boylece 'ı' harfi (negatif oldugu icin) bu filtreden gecer ve hata vermez.*/
                
                if(!isalpha(gecici_yazi[k]) && (int)gecici_yazi[k] > 0) {
                    printf("HATA: İsim sadece harflerden oluşmalıdır !!!!!\n");
                    hata_var = 1;
                    break;
                }
            }
        }

        if(hata_var == 0) {
            strcpy(kisiler[i].isim, gecici_yazi);
            veri_dogru_mu = 1;
            // Girdi standartlara uygun oldugu ıcın degiskeni 1 yapıp donguden cıkarım.
        }
    }

    
    // ADIM 3 Soyisim Kontrolü
    veri_dogru_mu = 0;
    while(veri_dogru_mu == 0) {
        hata_var = 0;
        printf("Soyisim: ");
        scanf("%s", gecici_yazi);

        // Enter tuşu veya fazla karakterler için ilk başta buffer temizliyoruz.
        while ((gecici_buffer = getchar()) != '\n' && gecici_buffer != EOF);

        // Girdinin uzunluğunu kontrol ediyorum.
        if(strlen(gecici_yazi) > 29) { 
            printf("HATA: Soyisim çok uzun. Maksimum 29 karakter olabilir.\n");
            hata_var = 1;
        }

        if(hata_var == 0) {
            for(k = 0; k < strlen(gecici_yazi); k++) {
                // Yukarıda bahsettiğim aynı hileyi burada da uyguluyorum.
                if(!isalpha(gecici_yazi[k]) && (int)gecici_yazi[k] > 0) {
                    printf("HATA: Soyisim sadece harflerden oluşmalıdır !!!!!\n");
                    hata_var = 1;
                    break;
                }
            }
        }

        if(hata_var == 0) {
            strcpy(kisiler[i].soyisim, gecici_yazi);
            veri_dogru_mu = 1;
            //Girdinin dogrulugu artık teyit edilmis oluyor ve degisken degerini 1 yaparak donguden cıkıyorum.
        }
    }

    // ADIM 4 Yas kontrolu
    veri_dogru_mu = 0;
    while(veri_dogru_mu == 0) {
        hata_var = 0;
        printf("Yaş: ");
        scanf("%s", gecici_yazi);
        
        // Enter tuşu veya fazla karakterler için ilk başta buffer temizliyoruz.
        while ((gecici_buffer = getchar()) != '\n' && gecici_buffer != EOF);

        // Yas uzunlugunu kontrol edıyorum.
        if(strlen(gecici_yazi) > 3) {
            printf("HATA: Yaş bilgisi çok uzun !!!!!\n");
            hata_var = 1;
        }


        // Bu bolumde hem negatif deger almayı hemde harf gırmeyı engellemek adına isdigit() kullandım.
        if(hata_var == 0) {
            for(k = 0; k < strlen(gecici_yazi); k++) {
                if(!isdigit(gecici_yazi[k])) { 
                    printf("HATA: Yaş sadece rakam olmalıdır !!!!!\n");
                    hata_var = 1;
                    break;
                }
            }
        }

        if(hata_var == 0) {
            strcpy(kisiler[i].yas, gecici_yazi);
            veri_dogru_mu = 1;
            //Girilen girdi dogru bir formatta girildi degisken degerini 1 yapıp donguden cıkarım.
        }
    }

    
    // ADIM 5 Telefon numarası kontrolu
    veri_dogru_mu = 0;
    while(veri_dogru_mu == 0) {
        hata_var = 0;
        printf("Telefon No (Örnek: 0542 375 52 71): ");
        
        // Scanf yerine fgets kullanmamın nedeni boşlukları alması.
        fgets(gecici_yazi, 100, stdin);
        
        // Sondaki enter (\n) isaretini siliyoruz
        gecici_yazi[strcspn(gecici_yazi, "\n")] = 0;

        // Girdinin uzunlugunu kontrol ediyorum.
        if(strlen(gecici_yazi) > 14) {
            printf("HATA: Telefon numarası çok uzun. Max 14 karakter olmalı !!!!!\n");
            hata_var = 1;
        }

        // İçerik kontrolu yapıyorum harfmi bosluk varmı negatıf deger almısmı.
        if(hata_var == 0) {
            for(k = 0; k < strlen(gecici_yazi); k++) {
                // Karakterin rakam mı bosluk varmı bunu kontrol ederım .
                if(!isdigit(gecici_yazi[k]) && !isspace(gecici_yazi[k])) {
                    printf("HATA: Telefon numarasında harf veya sembol olamaz !!!!!\n");
                    hata_var = 1;
                    break;
                }
            }
        }

        
        if(hata_var == 0) {
            strcpy(kisiler[i].tel_no, gecici_yazi);
            veri_dogru_mu = 1;
            // Girdi teyit ediliyor ve döngüden çıkılıyor.
        }
    }

    
    // ADIM 6 Adres Kontrolü
    
    printf("Adres (Mahalle, Sokak vb. bosluk kullanabilirsiniz): ");
    fgets(kisiler[i].adres, 100, stdin); 
    
    // Sondaki enter (\n) isaretini siliyoruz .
    kisiler[i].adres[strcspn(kisiler[i].adres, "\n")] = 0;


    // ADIM 7 Hattın İlk Tarihi kontrolü
    veri_dogru_mu = 0;
    while(veri_dogru_mu == 0) {
        printf("Hattin Ilk Tarihi (Gun Ay Yil): ");
        scanf("%d %d %d", &kisiler[i].ilk_tarih.gun, &kisiler[i].ilk_tarih.ay, &kisiler[i].ilk_tarih.yil);
        
        // 01 31 arası girsin diye bir kontrol yapıyorum.
        if(kisiler[i].ilk_tarih.gun < 1 || kisiler[i].ilk_tarih.gun > 31) {
            printf("HATA: Gun 1 ile 31 arasinda olmalidir!\n");
        }
        // Aynı olayı ay içinde yapıyorum.
        else if(kisiler[i].ilk_tarih.ay < 1 || kisiler[i].ilk_tarih.ay > 12) {
            printf("HATA: Ay 1 ile 12 arasinda olmalidir!\n");
        }
        else {
            veri_dogru_mu = 1; 
        }
    }

    // ADIM 8 Mevcut Operatör Kontrolü
    veri_dogru_mu = 0;
    while(veri_dogru_mu == 0) {
        hata_var = 0;
        printf("Mevcut Operator: ");
        scanf("%s", kisiler[i].op_ad); // Tek kelime varsayarım.

        // Buffer temizliği yaparım.
        while ((gecici_buffer = getchar()) != '\n' && gecici_buffer != EOF); 

        // Girdinin içerisinde rakam varmı kontrolü yaparım.
        for(k = 0; k < strlen(kisiler[i].op_ad); k++) {
            if(isdigit(kisiler[i].op_ad[k])) {
                printf("HATA: Operator isminde rakam olamaz!\n");
                hata_var = 1;
                break;
            }
        }

        if(hata_var == 0) veri_dogru_mu = 1;
    }

    // ADIM 9 Kampanya İsmi kontrolü
    veri_dogru_mu = 0;
    while(veri_dogru_mu == 0) {
        hata_var = 0;
        printf("Kampanya Ismi: ");
        fgets(kisiler[i].kampanya, 30, stdin);
        
        // Enter karakterini silerim sıkıntı olmasın yazı bozulmasın.
        kisiler[i].kampanya[strcspn(kisiler[i].kampanya, "\n")] = 0;

        // İçerik kontrolü yaparım.
        for(k = 0; k < strlen(kisiler[i].kampanya); k++) {
            if(isdigit(kisiler[i].kampanya[k])) {
                printf("HATA: Kampanya isminde rakam olamaz! Sadece harf giriniz.\n");
                hata_var = 1;
                break;
            }
        }

        if(hata_var == 0) veri_dogru_mu = 1;
    }

    // ADIM 10 Tarife başlangıç tarihi kontrolü 
    veri_dogru_mu = 0;
    while(veri_dogru_mu == 0) {
        printf("Tarife Baslangic (Gun Ay Yil): ");
        scanf("%d %d %d", &kisiler[i].tarife_bas.gun, &kisiler[i].tarife_bas.ay, &kisiler[i].tarife_bas.yil);

        if(kisiler[i].tarife_bas.gun < 1 || kisiler[i].tarife_bas.gun > 31) {
            printf("HATA: Gun 1-31 arasi olmali !!!!!\n");
        } else if(kisiler[i].tarife_bas.ay < 1 || kisiler[i].tarife_bas.ay > 12) {
            printf("HATA: Ay 1-12 arasi olmali !!!!!\n");
        } else {
            veri_dogru_mu = 1;
        }
    }


    // ADIM 11 Tarife son tarih kontrolü    
    veri_dogru_mu = 0;
    while(veri_dogru_mu == 0) {
        printf("Tarife Bitis (Gun Ay Yil): ");
        scanf("%d %d %d", &kisiler[i].tarife_son.gun, &kisiler[i].tarife_son.ay, &kisiler[i].tarife_son.yil);

        // Standart olarak tarih kontrolümü yaparım.
        if(kisiler[i].tarife_son.gun < 1 || kisiler[i].tarife_son.gun > 31 || 
           kisiler[i].tarife_son.ay < 1 || kisiler[i].tarife_son.ay > 12) {
            printf("HATA: Gecersiz tarih girdiniz (Gun 1-31, Ay 1-12)!\n");
            continue; 
        }

        // Eğer tarih öncesini girerse hata versin diye bir bayrak belirlerim.
        int tarih_hatali = 0;

        // Başlangıc yılı > bitiş ise hatalı çıkar.
        if(kisiler[i].tarife_son.yil < kisiler[i].tarife_bas.yil) {
            tarih_hatali = 1;
        }
        // Yıllar eşitse ay kontrolü yaparım.
        else if(kisiler[i].tarife_son.yil == kisiler[i].tarife_bas.yil) {
            if(kisiler[i].tarife_son.ay < kisiler[i].tarife_bas.ay) {
                tarih_hatali = 1;
            }
            // Aylar da eşitse gün kontrolü yaparım.
            else if(kisiler[i].tarife_son.ay == kisiler[i].tarife_bas.ay) {
                if(kisiler[i].tarife_son.gun < kisiler[i].tarife_bas.gun) {
                    tarih_hatali = 1;
                }
            }
        }

        if(tarih_hatali) {
            printf("HATA: Bitis tarihi, Baslangic tarihinden once olamaz!\n");
            printf("    Baslangic: %d.%d.%d olarak girmistiniz.\n", 
                    kisiler[i].tarife_bas.gun, kisiler[i].tarife_bas.ay, kisiler[i].tarife_bas.yil);
        } else {
            veri_dogru_mu = 1; // Her sey yolunda
        }
    }

    // Gecmis bilgileri otomatik doldur.
    strcpy(kisiler[i].eski_op1, "Bulunmuyor");
    strcpy(kisiler[i].eski_op2, "Bulunmuyor");

    mevcut_abone++;
    // Ekrana yazdırırım bilgileri.
    printf("Abone sisteme eklendi.\n");
    printf("Ad Soyad : %s %s\n",kisiler[i].isim, kisiler[i].soyisim);
    printf("TC No    : %s\n",kisiler[i].tc_no);
    printf("Telefon  : %s\n",kisiler[i].tel_no);
    printf("Operator : %s\n",kisiler[i].op_ad);
    printf("Kampanya ismi : %s\n",kisiler[i].kampanya);
    printf("=========================================\n\n");
    
}

void abone_sil() {
    char silinecek_tc[20]; // Yukarıda ki bölümde yaptığımız gibi tc ' yi geçici bir değişkende tutacağım.
    int i, j;              // Döngü için sayaçlarımı tanımlarım yukarıya tanımlamak daha rahat oluyor.
    int bulundu_mu = 0;    // Bu bölümde de bayrak tekniğini kullanacağım.
    char gecici_buffer;    // Buffer temizliği için değişken tanımlayacağım yine.

    // Kontrol için değişken eklerim.
    int veri_dogru_mu = 0; 
    int k, hata_var; 

    printf("\n--- ABONE SILME ISLEMI ---\n");

    // TC kontrol bölümü.
    while(veri_dogru_mu == 0) {
        hata_var = 0;
        printf("Silinecek Abonenin TC Kimlik Numarasi: "); 
        scanf("%s", silinecek_tc);

        // Artık bu temizleme işlemini alışkanlık haline getirdik.
        while ((gecici_buffer = getchar()) != '\n' && gecici_buffer != EOF);

        // Uzunluk Kontrolü yaparım.
        if(strlen(silinecek_tc) != 11) {
            printf("HATA: TC Kimlik No tam 11 haneli olmalidir !!!!!\n");
            hata_var = 1;
        }

        // İçerik Kontrolü yaparım.
        if(hata_var == 0) {
            for(k = 0; k < strlen(silinecek_tc); k++) {
                if(!isdigit(silinecek_tc[k])) {
                    printf("HATA: TC sadece rakamlardan olusmalidir (Harf, bosluk veya isaret olamaz)!\n");
                    hata_var = 1;
                    break;
                }
            }
        }

        // Hata yoksa döngüden çıkarım.
        if(hata_var == 0) {
            veri_dogru_mu = 1;
        }
    }
    

    // Diziyi tamamen tararım verilen tc ' de ki kişiyi bulmak için.
    for(i = 0; i < mevcut_abone; i++) {
        
        // Eğer strcmp sonucu 0 dönerse kişiyi bulurum .
        if(strcmp(kisiler[i].tc_no, silinecek_tc) == 0) {
            
            bulundu_mu = 1; 
            
            printf("\nAbone bulundu : %s %s isimli abone siliniyor !!!\n", kisiler[i].isim, kisiler[i].soyisim);

            /* Bu bölümde de verilen kişiyi sildikten sonra kaydırma işlemini kullanacağım.
            Böylelikle her elemanın yerine bir sonraki elemanı kopyalacağız.Böylece silinen kişi yerine bir üzerindeki
            kişi yazılmayacak.
            */
            
            for(j = i; j < mevcut_abone - 1; j++) {
                kisiler[j] = kisiler[j+1];
            }

            // Eleman silindiğinde mevcut aboneyi azaltırım.
            mevcut_abone--;

            printf("Abone başarıyla silindi.Güncel abone sayısı : %d\n", mevcut_abone);
            
            // Elemanı bulup sildik artık çıkabiliriz.
            break; 
        }
    }

    // Herşeyi bitirdikten sonra eğer bulundu_mu değikenimiz 0 ise bu kişi bulunmamıştır.
    if(bulundu_mu == 0) {
        printf("\nHATA: Girdiğiniz TC numarasina (%s) ait bir kayıt bulunamadi.\n", silinecek_tc);
    }
}
void abone_guncel() {
    char aranan_tel[20];   
    int i, secim;          
    int bulundu_mu = 0;    
    char gecici_buffer;    // Temizlik için her yerde bunu tanımladım.

    // Kontrol Degiskenleri tanımlarım.
    int veri_dogru_mu = 0; 
    int k, hata_var; 
    

    // fgets çalışmadan önce temizliyorum.
    while ((gecici_buffer = getchar()) != '\n' && gecici_buffer != EOF);
    // -----------------------

    printf("\n--- ABONE BILGILERI GUNCELLEME ---\n");
    printf("Bilgilerini güncellemek istediğiniz telefon numarasını girin: ");
    printf("\n(Ornek: 0572 824 13 52): ");
    
    fgets(aranan_tel, 20, stdin);
    
    // Sondaki enter (\n) karakterini temizliyoruz (Daha önce yapmıştık.)
    aranan_tel[strcspn(aranan_tel, "\n")] = 0;

    for(i = 0; i < mevcut_abone; i++) {
        if(strcmp(kisiler[i].tel_no, aranan_tel) == 0) {
            
            bulundu_mu = 1; 
            
            printf("\nAbone Bulundu: %s %s\n", kisiler[i].isim, kisiler[i].soyisim);
            printf("--------------------------------\n");
            printf("1. Adres Güncelle\n");
            printf("2. Mevcut Operator Güncelle\n");
            printf("3. Kampanya Güncelle\n");
            printf("0. İptal / Ana Menüye Dön\n");
            printf("--------------------------------\n");
            printf("Seciminiz: ");
            scanf("%d", &secim);

            // Seçim yaptıktan sonra yine string gireceğimiz için temizliyorum.
            while ((gecici_buffer = getchar()) != '\n' && gecici_buffer != EOF);

            switch(secim) {
                case 1:
                    // Adreste rakam olabilir (No: 5 gibi), o yuzden kontrol koymuyoruz.
                    printf("Yeni Adres: ");
                    fgets(kisiler[i].adres, 100, stdin);
                    kisiler[i].adres[strcspn(kisiler[i].adres, "\n")] = 0;
                    printf("Adres bilgisi güncellendi.\n");
                    break;
                
                case 2:
                    // Operatör kontrolu
                    veri_dogru_mu = 0;
                    while(veri_dogru_mu == 0) {
                        hata_var = 0;
                        printf("Yeni Operator Ismi: ");
                        fgets(kisiler[i].op_ad, 15, stdin);
                        kisiler[i].op_ad[strcspn(kisiler[i].op_ad, "\n")] = 0;
                        
                        // İçerik kontrolü
                        for(k = 0; k < strlen(kisiler[i].op_ad); k++) {
                            if(isdigit(kisiler[i].op_ad[k])) {
                                printf("HATA: Operator isminde rakam olamaz!\n");
                                hata_var = 1;
                                break;
                            }
                        }
                        if(hata_var == 0) {
                            veri_dogru_mu = 1;
                            printf("Operator bilgisi güncellendi.\n");
                        }
                    }
                    break;

                case 3:
                    // Kampanya kontrolü
                    veri_dogru_mu = 0;
                    while(veri_dogru_mu == 0) {
                        hata_var = 0;
                        printf("Yeni Kampanya İsmi: ");
                        fgets(kisiler[i].kampanya, 30, stdin);
                        kisiler[i].kampanya[strcspn(kisiler[i].kampanya, "\n")] = 0;
                        
                        // Icerik Kontrolu
                        for(k = 0; k < strlen(kisiler[i].kampanya); k++) {
                            if(isdigit(kisiler[i].kampanya[k])) {
                                printf("HATA: Kampanya isminde rakam olamaz!\n");
                                hata_var = 1;
                                break;
                            }
                        }
                        if(hata_var == 0) {
                            veri_dogru_mu = 1;
                            printf("Kampanya bilgisi güncellendi.\n");
                        }
                    }
                    break;

                case 0:
                    printf("İşlem iptal edildi.\n");
                    break;

                default:
                    printf("Hatalı secim yaptiniz.\n");
                    break;
            }
            break; 
        }
    }

    if(bulundu_mu == 0) {
        printf("\nHATA: Girdiğiniz numaraya (%s) ait kayıt bulunamadı !!!!!\n", aranan_tel);
    }
}

void abone_ara() {
    // Yukarıda kullandığım aynı kontrol değişkenlerini kullandım.
    int secim;
    int i;
    int bulundu_mu = 0; 
    char aranan[30];    // Hem tc hem de isim sığabilsin diye 30 byte ' lık yer açtım.
    char gecici_buffer; 

    // Kontrol değişkenlerini buraya da ekledim. 
    int veri_dogru_mu = 0;
    int k, hata_var;

    printf("\n--- ABONE ARAMA EKRANI ---\n");
    printf("1. Isim veya Soyisim ile Arama\n");
    printf("2. TC Kimlik No ile Arama\n");
    printf("Seciminiz: ");
    scanf("%d", &secim);

    // Sayi aldiktan sonra string (yazi) alacagimiz icin buffer temizliyorum.
    while ((gecici_buffer = getchar()) != '\n' && gecici_buffer != EOF);

    // Kullanicidan aranacak veriyi alalim.
    if(secim == 1) {
        
        // İsim / Soyisim girdi kontrolü.
        veri_dogru_mu = 0;
        while(veri_dogru_mu == 0) {
            hata_var = 0;
            printf("Aranacak Isim veya Soyisimi giriniz: ");
            scanf("%s", aranan); 

            // Buffer temizligi yaparım.
            while ((gecici_buffer = getchar()) != '\n' && gecici_buffer != EOF);

            // Uzunluk kontrolü yaparım.
            if(strlen(aranan) > 29) {
                printf("HATA: Cok uzun bir deger girdiniz!\n");
                hata_var = 1;
            }

            // İçerik kontrolü yaparım.
            if(hata_var == 0) {
                for(k = 0; k < strlen(aranan); k++) {
                    // Harf ve özel karakter kontrolu yapıyorum .
                    if(!isalpha(aranan[k]) && (int)aranan[k] > 0) {
                        printf("HATA: Isim/Soyisim aramasi sadece harflerle yapilabilir!\n");
                        hata_var = 1;
                        break;
                    }
                }
            }

            if(hata_var == 0) veri_dogru_mu = 1;
        }
        

    } 
    else if(secim == 2) {
        
        // TC girdi kontrolü
        veri_dogru_mu = 0;
        while(veri_dogru_mu == 0) {
            hata_var = 0;
            printf("Aranacak TC Numarasini giriniz: ");
            scanf("%s", aranan);

            // Buffer temizligi 
            while ((gecici_buffer = getchar()) != '\n' && gecici_buffer != EOF);

            // Uzunluk kontrolü
            if(strlen(aranan) != 11) {
                printf("HATA: TC Kimlik No 11 haneli olmalidir!\n");
                hata_var = 1;
            }

            // İçerik kontrolü 
            if(hata_var == 0) {
                for(k = 0; k < strlen(aranan); k++) {
                    if(!isdigit(aranan[k])) {
                        printf("HATA: TC aramasi sadece rakamlarla yapilabilir!\n");
                        hata_var = 1;
                        break;
                    }
                }
            }

            if(hata_var == 0) veri_dogru_mu = 1;
        }
        

    } 
    else {
        printf("Hatalı seçim yaptınız. Ana menüye dönülüyor.\n");
        return; 
    }

    printf("\n>>> Arama Sonuclari:\n");
    printf("--------------------------------------------------\n");

    // Tum diziyi bastan sona geziyoruz
    for(i = 0; i < mevcut_abone; i++) {
        
        // İsim / Soyisim arama
        if(secim == 1) {
            // Strcmp eğer 0 dönerse bulunmuştur veya operatörünü her ikiside olsa olur o yüzden kullanıyorum.
            if(strcmp(kisiler[i].isim, aranan) == 0 || strcmp(kisiler[i].soyisim, aranan) == 0) {
                printf("BULUNDU: %s %s\n", kisiler[i].isim, kisiler[i].soyisim);
                printf("         TC: %s | Tel: %s | Op: %s\n", kisiler[i].tc_no, kisiler[i].tel_no, kisiler[i].op_ad);
                printf("--------------------------------------------------\n");
                bulundu_mu = 1; // En az bir kisi bulduk
            }
        }
        
        // TC arama bölümü
        else if(secim == 2) {
            // TC numaraları eşsiz olduğu için direk arıyorum.
            if(strcmp(kisiler[i].tc_no, aranan) == 0) {
                printf("BULUNDU: %s %s\n", kisiler[i].isim, kisiler[i].soyisim);
                printf("         Adres: %s\n", kisiler[i].adres);
                printf("         Mevcut Op: %s (%s)\n", kisiler[i].op_ad, kisiler[i].kampanya);
                printf("--------------------------------------------------\n");
                bulundu_mu = 1;
            }
        }
    }

    // Döngü bitti bayrak hala 0 ' sa bulamamış demek ki program.
    if(bulundu_mu == 0) {
        printf("Uzgunuz, '%s' kriterine uygun bir kayit bulunamadi.\n", aranan);
    }
}
void rapor_tarih_degis() {
    int aranan_yil;
    int i;
    int sayac = 0;      
    char gecici_buffer; 

    printf("\n--- TARIH ARALIGINDA OPERATOR DEGISIKLIKLERI RAPORU ---\n");
    printf("Hangi yildaki degisiklikleri gormek istersiniz? (Ornek: 2022): ");
    scanf("%d", &aranan_yil);

    // Sayi aldiktan sonra buffer temizligi yapiyoruz
    while ((gecici_buffer = getchar()) != '\n' && gecici_buffer != EOF);

    printf("\n>>> %d Yilinda Operator Degistiren Aboneler:\n", aranan_yil);
    printf("------------------------------------------------------------\n");

    for(i = 0; i < mevcut_abone; i++) {
        
        // Op2 den Op 1 e geçiş kontrolu.
        if(strcmp(kisiler[i].eski_op2, "Bulunmuyor") != 0 && 
           kisiler[i].op2_bitis.yil == aranan_yil) {
            
            // Hedef operatörü pointer ile tutarım.
            char *hedef_op;
            
            // Eski op un varlığına bakarım.
            if(strcmp(kisiler[i].eski_op1, "Bulunmuyor") != 0) {
                hedef_op = kisiler[i].eski_op1;
            } else {
                // Eğer eski op 1 yoksa direkmen mevcut operatöre geçmiştir.
                hedef_op = kisiler[i].op_ad;
            }

            
            printf("%d. %s %s : %s -> %s\n", 
                   ++sayac, kisiler[i].isim, kisiler[i].soyisim, kisiler[i].eski_op2, hedef_op);
        }

        // Op1 ' den mevcut operatöre geçiş kontrolü
        if(strcmp(kisiler[i].eski_op1, "Bulunmuyor") != 0 && 
           kisiler[i].op1_bitis.yil == aranan_yil) {
            
            // eski operatöreden yeniye geçiş yaparım.
            printf("%d. %s %s : %s -> %s\n", 
                   ++sayac, kisiler[i].isim, kisiler[i].soyisim, kisiler[i].eski_op1, kisiler[i].op_ad);
        }
    }

    printf("------------------------------------------------------------\n");
    if(sayac == 0) {
        printf("Belirtilen yilda (%d) herhangi bir operator degisikligi bulunamadi.\n", aranan_yil);
    } else {
        printf("Toplam %d adet degisiklik tespit edildi.\n", sayac);
    }
}

void rapor_sadakat() {
    int i;
    // Sayaçlarımı tanımlarım.
    int turkcell_sadik = 0;
    int vodafone_sadik = 0;
    int turk_telekom_sadik = 0;
    int bimcell_sadik = 0;
    int diger_sadik = 0;

    printf("\n--- OPERATOR BAZLI MUSTERI SADAKATI RAPORU ---\n");
    printf("(Hic operator degistirmemis abonelerin sayisi)\n");
    printf("----------------------------------------------\n");

    for(i = 0; i < mevcut_abone; i++) {
        
        int sadik_mi = 0; // Sadıklık bayrağı tanımlarım.

        // Yok veya bulunmuyor ifadesi varmı diye kontrol ederim. Bu kısmı ben uydurdum.
        if(strcmp(kisiler[i].eski_op1, "Yok") == 0 || strcmp(kisiler[i].eski_op1, "Bulunmuyor") == 0) {
            sadik_mi = 1;
        }
        
        // Operatörleri karşılaştırırım 3 'de aynı mı diye.
        else if(strcmp(kisiler[i].op_ad, kisiler[i].eski_op1) == 0 && 
                strcmp(kisiler[i].op_ad, kisiler[i].eski_op2) == 0) {
            sadik_mi = 1;
        }

        // Yukarıdaki kontroller sonucu eklerim.
        if(sadik_mi == 1) {
            if(strcmp(kisiler[i].op_ad, "Turkcell") == 0) {
                turkcell_sadik++;
            }
            else if(strcmp(kisiler[i].op_ad, "Vodafone") == 0) {
                vodafone_sadik++;
            }
            else if(strcmp(kisiler[i].op_ad, "Turk Telekom") == 0) {
                turk_telekom_sadik++;
            }
            else if(strcmp(kisiler[i].op_ad, "Bimcell") == 0) {
                bimcell_sadik++;
            }
            else {
                diger_sadik++;
            }
        }
    }

    // Sonuçları yazdırma bölümü.
    printf("> Turkcell     : %d sadik abone.\n", turkcell_sadik);
    printf("> Vodafone     : %d sadik abone.\n", vodafone_sadik);
    printf("> Turk Telekom : %d sadik abone.\n", turk_telekom_sadik);
    printf("> Bimcell      : %d sadik abone.\n", bimcell_sadik);
    
    if(diger_sadik > 0) {
        printf("> Diger        : %d sadik abone.\n", diger_sadik);
    }
    
    printf("----------------------------------------------\n");
}

void rapor_kampanya_siralama() {
    // Farklı kampanya türleri ve adetlerinide tutabilmek adına tanımladım ek veriler olabilir.Sonuçta eklemeye devam edeceğiz.
    char kampanya_isimleri[50][30]; 
    int kampanya_adetleri[50];      
    
    int cesit_sayisi = 0; 
    int i, j, k;          
    int bulundu_mu;       

    // Geçici diziyi temizledim garantilemek için.
    for(i=0; i<50; i++) kampanya_adetleri[i] = 0;

    printf("\n--- KAMPANYA POPULARITE ANALIZI (Coktan Aza) ---\n");
    printf("--------------------------------------------------\n");

    // Tüm aboneleri tararım.
    for(i = 0; i < mevcut_abone; i++) {
        
        bulundu_mu = 0;

        // Kişilerin kampanyası eklenmiş mi kontrol ederim.
        for(j = 0; j < cesit_sayisi; j++) {
            if(strcmp(kisiler[i].kampanya, kampanya_isimleri[j]) == 0) {
                // Eger listede varsa sayisini 1 artirırım.
                kampanya_adetleri[j]++;
                bulundu_mu = 1;
                break;
            }
        }

        // Eger listede yoksa, yeni bir tür olarak eklerim.
        if(bulundu_mu == 0) {
            strcpy(kampanya_isimleri[cesit_sayisi], kisiler[i].kampanya);
            kampanya_adetleri[cesit_sayisi] = 1; // Ilk adeti 1 olsun
            cesit_sayisi++;
        }
    }

    // Bu bölümde klasik bubble sort sıralamasını uyarladım.    
    for(j = 0; j < cesit_sayisi - 1; j++) {
        for(k = 0; k < cesit_sayisi - 1 - j; k++) {
            
            // Bir önceki sayıdan büyükse yer değiştirme yaparım.
            if(kampanya_adetleri[k] < kampanya_adetleri[k+1]) {
                
                //Sayıları yer değiştiririm.
                int gecici_sayi = kampanya_adetleri[k];
                kampanya_adetleri[k] = kampanya_adetleri[k+1];
                kampanya_adetleri[k+1] = gecici_sayi;

                //Ek olarak isimleride yer değiştiririm aksi takdirde karışıklık olur.
                char gecici_isim[30];
                strcpy(gecici_isim, kampanya_isimleri[k]);
                strcpy(kampanya_isimleri[k], kampanya_isimleri[k+1]);
                strcpy(kampanya_isimleri[k+1], gecici_isim);
            }
        }
    }

   
    // Ekrana çıktı veririm.
    for(i = 0; i < cesit_sayisi; i++) {
        printf("> %-20s : %d abone\n", kampanya_isimleri[i], kampanya_adetleri[i]);
    }

    printf("--------------------------------------------------\n");
    printf("Toplam %d farkli kampanya turu listelendi.\n", cesit_sayisi);
}