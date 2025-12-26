#!/bin/bash

# miniRT Test Script - Sadece Zorunlu Kısım
# 42 School Evaluator Tarzı

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

PROGRAM="./miniRT"
PASSED=0
FAILED=0

echo "========================================"
echo "   miniRT Test Suite - Mandatory Part"
echo "========================================"
echo ""

# Program var mı kontrol et
if [ ! -f "$PROGRAM" ]; then
    echo -e "${RED}HATA: miniRT çalıştırılabilir dosyası bulunamadı!${NC}"
    echo "Önce 'make' komutunu çalıştırın."
    exit 1
fi

# Test fonksiyonu - HATA beklenen testler için
test_error() {
    local test_name="$1"
    local test_file="$2"
    local description="$3"
    
    echo -e "${YELLOW}Test: ${test_name}${NC}"
    echo "Dosya: $test_file"
    echo "Beklenen: Error"
    
    # Timeout ile çalıştır (pencere açarsa kill etmek için)
    output=$(timeout 1 $PROGRAM "$test_file" 2>&1)
    exit_code=$?
    
    # Exit code 124 = timeout (program çalışmaya devam etti, hata vermedi)
    if [ $exit_code -eq 124 ]; then
        echo -e "${RED}✗ BAŞARISIZ${NC} - Program hata vermedi, pencere açtı!"
        echo "NOT: Parser bu hatayı yakalayamıyor - program zayıflığı"
        ((FAILED++))
    # Error kontrolü (exit code != 0 VEYA "Error" yazısı var mı)
    elif [ $exit_code -ne 0 ] || echo "$output" | grep -qi "error"; then
        echo -e "${GREEN}✓ GEÇTI${NC} - Hata mesajı: $(echo "$output" | head -n 1)"
        ((PASSED++))
    else
        echo -e "${RED}✗ BAŞARISIZ${NC} - Program hata vermedi!"
        echo "Çıktı: $output"
        ((FAILED++))
    fi
    echo ""
}

# Test fonksiyonu - BAŞARI beklenen testler için
test_success() {
    local test_name="$1"
    local test_file="$2"
    local description="$3"
    
    echo -e "${YELLOW}Test: ${test_name}${NC}"
    echo "Dosya: $test_file"
    echo "Beklenen: Success"
    
    # Timeout ile çalıştır (sonsuz döngüye girmemesi için)
    timeout 2 $PROGRAM "$test_file" 2>&1 &
    pid=$!
    sleep 0.5
    
    # Process hala çalışıyor mu?
    if ps -p $pid > /dev/null 2>&1; then
        echo -e "${GREEN}✓ GEÇTI${NC} - Program çalıştı"
        kill $pid 2>/dev/null
        wait $pid 2>/dev/null
        ((PASSED++))
    else
        wait $pid 2>/dev/null
        exit_code=$?
        echo -e "${RED}✗ BAŞARISIZ${NC} - Program hata verdi (exit code: $exit_code)"
        ((FAILED++))
    fi
    echo ""
}

# Argüman testleri
echo "=== 1. ARGÜMAN TESTLERİ ==="
echo ""

echo -e "${YELLOW}Test: Argüman yok${NC}"
output=$($PROGRAM 2>&1)
if [ $? -ne 0 ] || echo "$output" | grep -qi "error"; then
    echo -e "${GREEN}✓ GEÇTI${NC}"
    ((PASSED++))
else
    echo -e "${RED}✗ BAŞARISIZ${NC}"
    ((FAILED++))
fi
echo ""

echo -e "${YELLOW}Test: Çok fazla argüman${NC}"
output=$($PROGRAM maps/test_perfect_minimal.rt extra_arg 2>&1)
if [ $? -ne 0 ] || echo "$output" | grep -qi "error"; then
    echo -e "${GREEN}✓ GEÇTI${NC}"
    ((PASSED++))
else
    echo -e "${RED}✗ BAŞARISIZ${NC}"
    ((FAILED++))
fi
echo ""

echo -e "${YELLOW}Test: Var olmayan dosya${NC}"
output=$($PROGRAM nonexistent_file.rt 2>&1)
if [ $? -ne 0 ] || echo "$output" | grep -qi "error"; then
    echo -e "${GREEN}✓ GEÇTI${NC}"
    ((PASSED++))
else
    echo -e "${RED}✗ BAŞARISIZ${NC}"
    ((FAILED++))
fi
echo ""

# Dosya uzantısı testleri
echo "=== 2. DOSYA UZANTISI TESTLERİ ==="
echo ""

test_error "Yanlış uzantı (.txt)" "maps/test_wrong_extension.txt" "txt uzantısı hata vermeli"
test_error "Uzantı yok" "maps/test_no_extension" "Uzantısız dosya hata vermeli"

# Global element testleri
echo "=== 3. GLOBAL ELEMENT TESTLERİ ==="
echo ""

test_error "Ambient eksik" "maps/test_missing_ambient.rt" "A eksik"
test_error "Camera eksik" "maps/test_missing_camera.rt" "C eksik"
test_error "Light eksik" "maps/test_missing_light.rt" "L eksik"
test_error "Boş dosya" "maps/test_empty.rt" "Boş dosya"

# Çoğaltma testleri
echo "=== 4. ÇOĞALTMA TESTLERİ ==="
echo ""

test_error "Çift Ambient" "maps/test_double_ambient.rt" "İki A tanımı"
test_error "Çift Camera" "maps/test_double_camera.rt" "İki C tanımı"
test_error "Çift Light" "maps/test_double_light.rt" "İki L tanımı"

# Tanımlayıcı testleri
echo "=== 5. TANIMLAYICI TESTLERİ ==="
echo ""

test_error "Büyük harf Sphere" "maps/test_wrong_case_sphere.rt" "Sp yerine sp"
test_error "Büyük harf Plane" "maps/test_wrong_case_plane.rt" "PL yerine pl"
test_error "Büyük harf Cylinder" "maps/test_wrong_case_cylinder.rt" "Cy yerine cy"
test_error "Bilinmeyen tanımlayıcı" "maps/test_unknown_identifier.rt" "cone tanınmamalı"

# Vektör testleri
echo "=== 6. VEKTÖR TESTLERİ ==="
echo ""

test_error "Normalize edilmemiş camera" "maps/test_unnormalized_camera.rt" "0,0,5 normalize değil"
test_error "Normalize edilmemiş plane" "maps/test_unnormalized_plane.rt" "0,10,0 normalize değil"
test_error "Normalize edilmemiş cylinder" "maps/test_unnormalized_cylinder.rt" "0,5,0 normalize değil"
test_error "Sıfır vektör camera" "maps/test_zero_vector_camera.rt" "0,0,0 vektörü"
test_error "Sıfır vektör plane" "maps/test_zero_vector_plane.rt" "0,0,0 normal"

# Aralık testleri
echo "=== 7. ARALIK TESTLERİ ==="
echo ""

test_error "Ambient ratio negatif" "maps/test_ambient_ratio_negative.rt" "ratio < 0"
test_error "Ambient ratio > 1" "maps/test_ambient_ratio_over_one.rt" "ratio > 1"
test_error "Light ratio negatif" "maps/test_light_ratio_negative.rt" "ratio < 0"
test_error "Light ratio > 1" "maps/test_light_ratio_over_one.rt" "ratio > 1"
test_error "FOV negatif" "maps/test_fov_negative.rt" "FOV < 0"
test_error "FOV sıfır" "maps/test_fov_zero.rt" "FOV = 0"
test_error "FOV > 180" "maps/test_fov_over_180.rt" "FOV > 180"
test_error "RGB negatif" "maps/test_rgb_negative.rt" "RGB < 0"
test_error "RGB > 255" "maps/test_rgb_over_255.rt" "RGB > 255"

# Obje doğrulama testleri
echo "=== 8. OBJE DOĞRULAMA TESTLERİ ==="
echo ""

test_error "Sphere çap sıfır" "maps/test_sphere_zero_diameter.rt" "diameter = 0"
test_error "Sphere çap negatif" "maps/test_sphere_negative_diameter.rt" "diameter < 0"
test_error "Cylinder çap sıfır" "maps/test_cylinder_zero_diameter.rt" "diameter = 0"
test_error "Cylinder yükseklik negatif" "maps/test_cylinder_negative_height.rt" "height < 0"
test_error "Eksik sphere parametresi" "maps/test_missing_sphere_parameter.rt" "Parametre eksik"
test_error "Fazla sphere parametresi" "maps/test_extra_sphere_parameter.rt" "Fazla parametre"

# Sayı parsing testleri
echo "=== 9. SAYI PARSING TESTLERİ ==="
echo ""

test_error "Sayısal olmayan değer" "maps/test_non_numeric.rt" "abc"
test_error "Çift negatif" "maps/test_double_negative.rt" "--5"
test_error "Bilimsel gösterim" "maps/test_scientific_notation.rt" "1e5"
test_error "Eksik vektör elemanı" "maps/test_incomplete_vector.rt" "İki eleman"
test_error "Eksik RGB değeri" "maps/test_incomplete_rgb.rt" "İki RGB değeri"

# Format testleri
echo "=== 10. FORMAT TESTLERİ ==="
echo ""

test_error "İki element bir satır" "maps/test_two_elements_one_line.rt" "Aynı satırda iki element"
test_success "Çoklu boşluk" "maps/test_multiple_spaces.rt" "Birden fazla boşluk OK"

# Sıra testleri
echo "=== 11. SIRA TESTLERİ ==="
echo ""

test_success "Ters sıra" "maps/test_reverse_order.rt" "Elementler ters sırada"
test_success "Objeler önce" "maps/test_objects_before_globals.rt" "Objeler global'lerden önce"

# Başarılı test
echo "=== 12. GEÇERLİ TEST ==="
echo ""

test_success "Mükemmel minimal sahne" "maps/test_perfect_minimal.rt" "Tam geçerli sahne"

# Sonuçlar
echo "========================================"
echo "           TEST SONUÇLARI"
echo "========================================"
echo -e "${GREEN}Geçen testler: $PASSED${NC}"
echo -e "${RED}Başarısız testler: $FAILED${NC}"
echo -e "Toplam: $((PASSED + FAILED))"
echo ""

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}🎉 TÜM TESTLER BAŞARILI! 🎉${NC}"
    echo "Program parser'ı sağlam!"
    exit 0
else
    echo -e "${RED}⚠️  BAZI TESTLER BAŞARISIZ OLDU ⚠️${NC}"
    echo ""
    echo "Başarısız testler programın parser zayıflıklarını gösteriyor:"
    echo "• FOV=0: Geçersiz FOV değeri kabul ediliyor"
    echo "• Non-numeric (abc): atoi/atof yanlış parse ediyor"
    echo "• Double negative (--5): İşaret kontrolü eksik"
    echo "• Scientific notation (1e5): Format kontrolü eksik"
    echo ""
    echo "Bu sorunları düzeltmek için parser kodunu güçlendirin!"
    exit 1
fi
