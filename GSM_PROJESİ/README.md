# GSM Abone Yönetim Sistemi (GSM Subscriber Management System)

Bu proje, C programlama dili kullanılarak geliştirilmiş, konsol tabanlı bir telekomünikasyon abone yönetim sistemidir. Sistem; abone kaydı oluşturma, silme, güncelleme işlemlerinin yanı sıra, operatör sadakat analizi ve kampanya popülarite sıralaması gibi analitik raporlar sunmaktadır.

## 🚀 Özellikler

Proje, temel CRUD (Create, Read, Update, Delete) işlemlerinin ötesinde veri doğrulama ve raporlama yeteneklerine sahiptir:

* **Abone Yönetimi:**
    * **Kayıt Ekleme:** TC Kimlik, Telefon No, İsim gibi verilerin format kontrolü (Input Validation) yapılarak eklenmesi.
    * **Kayıt Silme:** Silinen abonenin ardından dizideki boşluğu kapatan kaydırma (shifting) algoritması.
    * **Güncelleme:** Mevcut abonelerin adres, operatör ve kampanya bilgilerinin güncellenmesi.
* **Arama Motoru:**
    * İsim/Soyisim veya TC Kimlik Numarasına göre abone arama.
* **Analitik Raporlar:**
    * **Tarih Bazlı Operatör Değişimi:** Belirli bir yılda operatör değiştiren kullanıcıların listelenmesi.
    * **Sadakat Analizi:** Hiç operatör değiştirmemiş "sadık" müşterilerin operatör bazlı dağılımı.
    * **Kampanya Popülaritesi:** **Bubble Sort** algoritması kullanılarak kampanyaların en çok tercih edilenden en aza doğru sıralanması.

## 🛠 Kullanılan Teknolojiler ve Algoritmalar

* **Dil:** C
* **Veri Yapıları:** Structs (Yapılar), Arrays (Diziler), Pointers (İşaretçiler).
* **Algoritmalar:**
    * **Bubble Sort:** Kampanya kullanım sayılarını sıralamak için.
    * **Linear Search:** Abone arama ve veri filtreleme işlemleri için.
    * **Array Shifting:** Silme işlemi sonrası veri bütünlüğünü korumak için.
* **Kütüphaneler:** `<string.h>`, `<ctype.h>`, `<stdlib.h>`, `<locale.h>`

## 📂 Proje Yapısı

Proje iki ana dosyadan oluşmaktadır:

1.  `main.c`: Ana uygulama mantığı, menü sistemi ve fonksiyon tanımları.
2.  `veri_seti.h`: Veri yapılarını (Struct) ve global değişkenleri barındıran başlık dosyası.

> **Not:** Derleme yapabilmek için `veri_seti.h` dosyasının proje dizininde bulunduğundan emin olun.

## 💻 Kurulum ve Çalıştırma

Projeyi kendi bilgisayarınızda çalıştırmak için aşağıdaki adımları izleyin:

1.  Projeyi klonlayın veya indirin.
2.  Terminal veya komut istemcisini açın.
3.  Aşağıdaki komut ile derleyin (GCC derleyicisi gerektirir):

```bash
gcc main.c -o gsm_sistemi