# Password Manager
Password Manager to aplikacja do zarządzania hasłami, umożliwiająca ich dodawanie, edytowanie, usuwanie oraz sortowanie. Program pozwala również na przypisywanie haseł do kategorii oraz szyfrowanie plików z hasłami, aby zapewnić ich bezpieczeństwo.

## Funkcjonalności
1. Logowanie
- Wymaga podania poprawnego hasła do uruchomienia aplikacji.
- Rejestruje każdą próbę logowania (udaną lub nieudaną) w pliku timestamp.txt.

2. Zarządzanie hasłami
- Wyszukiwanie haseł po nazwie, haśle lub kategorii.
- Dodawanie nowych haseł z możliwością generowania bezpiecznych, losowych haseł.
- Edytowanie i usuwanie istniejących haseł.
- Sortowanie haseł w plikach.

3. Zarządzanie kategoriami
- Tworzenie nowych kategorii, które automatycznie zapisują dane do dedykowanych plików.
- Usuwanie kategorii wraz z przypisanymi plikami.

4. Szyfrowanie danych
- Wszystkie pliki z hasłami są szyfrowane za pomocą operacji XOR z kluczem.

5. Walidacja haseł
- Wbudowana funkcja sprawdzająca bezpieczeństwo haseł (duże litery, małe litery, znaki specjalne).
- Generowanie losowych haseł na podstawie wybranych parametrów.
