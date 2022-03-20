#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct Red oda1;
struct Green oda2;
struct Blue oda3;
FILE *ucret;
FILE *fptr;
FILE *koltuk;
enum film1
{
    matine1 = 1,
    matine2,
    matine3,
    matine4,
    matine5
} s1;
struct Red
{
    enum film1 s1;
};
struct Green
{
    enum film1 s1;
};
struct Blue
{
    enum film1 s1;
};
int ogr_ucret = 20, tam_ucret = 30;

void AnaMenu();
void DosyayaVeriGirme();
void DosyadanVeriKontrolu();
void koltuk_atama();
int koltuk_okuma(int a);
void Ucretlendirme();
void UcretHesaplama();
void matineSec();
void SalonOdaSec();

void AnaMenu()
{
    int sec;
    printf("\t\t\t\tSinamamiza Hosgeldiniz\n\n");
    printf("1-Oda-matine secmek icin.\n2-Hasilat Bilgisi.\n\n");
    printf("Hangi islemi yapmak istersiniz:");
    scanf("%d", &sec);
    switch (sec)
    {
    case 1:
        SalonOdaSec();
        break;
    case 2:
        UcretHesaplama();
    }
}
void DosyayaVeriGirme()
{
    char ad_giris[50], sifre_giris[50];
    if ((access("sifre.txt", F_OK)) != -1) // dosya kontrolu yapar , dosya varsa direk ıd ve sifre kontrolu yapar.
        DosyadanVeriKontrolu();

    else
    { // dosya yoksa dosya olusturulur
        fptr = fopen("sifre.txt", "w");
        if (fptr == NULL)
        {
            printf("Dosya Acilmiyor!");
            exit(1);
        }
        printf("Kullanici adi:");
        scanf("%s", &ad_giris);
        printf("Sifre:");
        scanf("%s", &sifre_giris);
        fprintf(fptr, "%s %s", ad_giris, sifre_giris);
        printf("\nHesabiniz basariyla olusturuldu.\n");
        fclose(fptr);
    }
}
void DosyadanVeriKontrolu()
{
    char ad_kontrol[50], sifre_kontrol[50], adTut[50], sifreTut[50];
    fptr = fopen("sifre.txt", "r");
    if (fptr == NULL)
    {
        printf("Dosya Acilmiyor!");
        exit(1);
    }
    printf("Kullanici adi:"); // kullanici ad ve sifresini girsin.
    scanf("%s", &ad_kontrol);
    printf("Sifre:");
    scanf("%s", &sifre_kontrol);

    fscanf(fptr, "%s %s", adTut, sifreTut); // ad ve sifre karsilastiriliyor.
    if (strcmp(adTut, ad_kontrol) == 0)
    {
        if (strcmp(sifreTut, sifre_kontrol) == 0)
        {
            printf("Menuye yonlendiriliyorsunuz!\n\n\n");
            sleep(1);
            system("cls");
            AnaMenu();
        }
        else
        {
            printf("Sifreniz yanlis!\n");
            exit(1);
        }
    }
    else
    {
        printf("Kullanici adiniz yanlis!\n");
        exit(1);
    }
    fclose(fptr);
}
void koltuk_atama()
{
    int indis, tut;
    int sayilar[50], Koltuklar[50], *p;
    p = Koltuklar;
    koltuk = fopen("Koltuk.txt", "w");
    if (koltuk == NULL)
    {
        printf("Dosya Acilmiyor!");
        exit(1);
    }
    srand(time(NULL));
    for (int i = 0; i < 50; i++)
    {
        sayilar[i] = i;
    }
    for (int k = 0; k < 50; k++) // random indis oluşturma
    {
        indis = k + rand() % (50 - k);
        tut = sayilar[k];
        sayilar[k] = sayilar[indis];
        sayilar[indis] = tut;
    }
    for (int i = 0; i < 50; i++) // sayilar dizisi koltuk numarasına atama
    {
        *(p + i) = sayilar[i];
        if (*(p + i) == 0) // 0. indisi alirsa 50 yapsin
        {
            *(p + i) = 50;
        }
        fprintf(koltuk, "%d ", *(p + i));
    }
    fclose(koltuk);
}

int koltuk_okuma(int a)
{
    int koltuk_tut, Koltuk_No[50];
    koltuk = fopen("Koltuk.txt", "r");
    if (koltuk == NULL)
    {
        printf("Dosya Acilmiyor!");
        exit(1);
    }
    for (int i = 0; i < 50; ++i)
    {
        if (fscanf(koltuk, "%d", &koltuk_tut) == 1) // dosyadaki koltuk no'larini bir diziye atiyorum ve bunlari tek tek yazdirma
            Koltuk_No[i] = koltuk_tut;
        else
            break;
    }
    fclose(koltuk);
    return printf("Koltuk No: %d", Koltuk_No[a - 1]); // indis 0 dan basladigi icin indisi 1 azaltıyoruz
}
void Ucretlendirme()
{
    int secenek;

    if ((access("ucretler.txt", F_OK)) == -1) // Dosya varmı kontrolü
    {
        ucret = fopen("ucretler.txt", "w");
        if (ucret == NULL)
        {
            printf("Dosya Acilmiyor!");
            exit(1);
        }
        fclose(ucret);
    }
    ucret = fopen("ucretler.txt", "a+"); // Dosyaya ucretleri ekleme
    if (ucret == NULL)
    {
        printf("Dosya Acilmiyor!");
        exit(1);
    }
    printf("\tOgrenci misiniz?\n1-Evet\n2-Hayir\n\n"); // ucret atama
    scanf("%d", &secenek);
    if (secenek == 1)
    {
        printf("\nUcretiniz: %d TL\n", ogr_ucret);
        fprintf(ucret, "%d ", ogr_ucret);
    }
    else if (secenek == 2)
    {
        printf("\nUcretiniz: %d TL\n", tam_ucret);
        fprintf(ucret, "%d ", tam_ucret);
    }
    else
        printf("Yanlis secim!");
    fclose(ucret);
}
void UcretHesaplama() // tum matineleri hesaplar
{
    int indis = 0, ucretTut, Ucretler[50], hesap = 0;
    ucret = fopen("ucretler.txt", "r");
    if (ucret == NULL)
    {
        printf("Dosya Acilmiyor!");
        exit(1);
    }
    while (fscanf(ucret, "%d", &ucretTut) == 1) // dosyadaki tam sayilari okuyup diziye kaydetme
    {
        Ucretler[indis] = ucretTut;
        indis++;
    }
    for (int i = 0; i < indis; i++) // okudugum tam sayilarin toplamini gerceklestirme ve ucreti hesaplama
    {
        hesap += Ucretler[i];
    }
    printf("Toplam Ucret:%d", hesap);
    fclose(ucret);
}
void matineSec()
{
    int secim;
    printf("1-Matine1\n2-Matine2\n3-Matine3\n4-Matine4\n5-Matine5\n");
    printf("\nMatine seciniz:");
    scanf("%d", &secim);
    oda2.s1 = secim;
    oda1.s1 = secim;
    oda3.s1 = secim;
}
void SalonOdaSec()
{
    int salonSec, secim, musteri;
    printf("\tLutfen salon seciniz->\n");
    printf("1-Red\n2-Green\n3-Blue\n");
    scanf("%d", &salonSec);
    printf("\n\n");
    switch (salonSec)
    {
    case 1:
        matineSec();
        printf("\n");
        switch (oda1.s1)
        {
        case matine1:
            printf("Seciminiz matin1 Saat 10:00'da baslayacak.\n");
            if ((access("Koltuk.txt", F_OK)) == -1) // Dosya yoksa dosya olustururlur
            {
                koltuk_atama();
                printf("Kacinci musteri: "); // manuel sayac arttırma
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            else // dosya varsa buraya gir ve direk koltuk ata
            {
                printf("\nKacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            printf("\n");
            Ucretlendirme(); // Musterinin ucreti hesaplaniyor
            break;
        case matine2:
            printf("Seciminiz matin2 Saat 13:00'da baslayacak.\n");
            if ((access("Koltuk.txt", F_OK)) == -1)
            {
                koltuk_atama();
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            else
            {
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            printf("\n");
            Ucretlendirme();
            break;
        case matine3:
            printf("Seciminiz matin3 Saat 16:00'da baslayacak.");
            if ((access("Koltuk.txt", F_OK)) == -1)
            {
                koltuk_atama();
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            else
            {
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            printf("\n");
            Ucretlendirme();
            break;
        case matine4:
            printf("Seciminiz matin4 Saat 19:00'da baslayacak.\n");
            if ((access("Koltuk.txt", F_OK)) == -1)
            {
                koltuk_atama();
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            else
            {
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            printf("\n");
            Ucretlendirme();
            break;
        case matine5:
            printf("Seciminiz matin5 Saat 22:00'da baslayacak.\n");
            if ((access("Koltuk.txt", F_OK)) == -1)
            {
                koltuk_atama();
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            else
            {
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            printf("\n");
            Ucretlendirme();
            break;
        default:
            printf("Yanlis secim yaptiniz.");
        }
        break;
    case 2:
        matineSec();
        printf("\n");
        switch (oda2.s1)
        {
        case matine1:
            printf("Seciminiz matin1 Saat 10:00'da baslayacak.\n");
            if ((access("Koltuk.txt", F_OK)) == -1)
            {
                koltuk_atama();
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            else
            {
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            printf("\n");
            Ucretlendirme();
            break;
        case matine2:
            printf("Seciminiz matin2 Saat 13:00'da baslayacak.\n");
            if ((access("Koltuk.txt", F_OK)) == -1)
            {
                koltuk_atama();
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            else
            {
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            printf("\n");
            Ucretlendirme();
            break;
        case matine3:
            printf("Seciminiz matin3 Saat 16:00'da baslayacak.\n");
            if ((access("Koltuk.txt", F_OK)) == -1)
            {
                koltuk_atama();
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            else
            {
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            printf("\n");
            Ucretlendirme();
            break;
        case matine4:
            printf("Seciminiz matin4 Saat 19:00'da baslayacak.\n");
            if ((access("Koltuk.txt", F_OK)) == -1)
            {
                koltuk_atama();
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            else
            {
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            printf("\n");
            Ucretlendirme();
            break;
        case matine5:
            printf("Seciminiz matin5 Saat 22:00'da baslayacak.\n");
            if ((access("Koltuk.txt", F_OK)) == -1)
            {
                koltuk_atama();
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            else
            {
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            printf("\n");
            Ucretlendirme();
            break;
        default:
            printf("Yanlis secim yaptiniz.");
        }
        break;
    case 3:
        matineSec();
        printf("\n");
        switch (oda3.s1)
        {
        case matine1:
            printf("Seciminiz matin1 Saat 10:00'da baslayacak.\n");
            if ((access("Koltuk.txt", F_OK)) == -1)
            {
                koltuk_atama();
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            else
            {
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            printf("\n");
            Ucretlendirme();
            break;
        case matine2:
            printf("Seciminiz matin2 Saat 13:00'da baslayacak.\n");
            if ((access("Koltuk.txt", F_OK)) == -1)
            {
                koltuk_atama();
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            else
            {
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            printf("\n");
            Ucretlendirme();
            break;
        case matine3:
            printf("Seciminiz matin3 Saat 16:00'da baslayacak.\n");
            if ((access("Koltuk.txt", F_OK)) == -1)
            {
                koltuk_atama();
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            else
            {
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            printf("\n");
            Ucretlendirme();
            break;
        case matine4:
            printf("Seciminiz matin4 Saat 19:00'da baslayacak.\n");
            if ((access("Koltuk.txt", F_OK)) == -1)
            {
                koltuk_atama();
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            else
            {
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            printf("\n");
            Ucretlendirme();
            break;
        case matine5:
            printf("Seciminiz matin5 Saat 22:00'da baslayacak.\n");
            if ((access("Koltuk.txt", F_OK)) == -1)
            {
                koltuk_atama();
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            else
            {
                printf("Kacinci musteri: ");
                scanf("%d", &musteri);
                koltuk_okuma(musteri);
            }
            printf("\n");
            Ucretlendirme();
            break;
        default:
            printf("Yanlis secim yaptiniz.");
        }
        break;
    default:
        printf("Yanlis secim yaptiniz.");
    }
}
int main()
{
    DosyayaVeriGirme();
    return 0;
}