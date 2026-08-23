// VPL 18. Vetor<T> whose valid index range is an arbitrary [inicio, fim]
// rather than [0, n), so operator[] translates the caller's index and
// Redimensionar has to preserve only the overlap between old and new bounds.
#include <iostream>


#ifndef VETOR_H_
#define VETOR_H_

#include <iostream>
#include <string>

using std::string;

template<typename Tipo>
class Vetor {
public:
    Vetor(int inicio, int fim) : inicio_(inicio), fim_(fim) {
        elementos_ = new Tipo[fim - inicio + 1]();
    }

    void Redimensionar(int inicio2, int fim2) {
        int tamanhoAntigo = fim_ - inicio_ + 1;
        int tamanhoNovo = fim2 - inicio2 + 1;
        Tipo* novosElementos = new Tipo[tamanhoNovo]();

        int maior_inicio = inicio_ < inicio2 ? inicio2 : inicio_;
        int menor_fim = fim_ > fim2 ? fim2 : fim_;

        for (int i = maior_inicio; i <= menor_fim; i++) {
            int a = i-inicio_;
            int b = i-inicio2;
            if (a>=0 && b>=0 && b<= tamanhoNovo && a<= tamanhoAntigo){
                novosElementos[b] = elementos_[a];
            }
        }

        delete[] elementos_;

        elementos_ = novosElementos;
        inicio_ = inicio2;
        fim_ = fim2;
    }

    Tipo& operator[](int i) {
        if (i < inicio_ || i > fim_) {
            throw std::out_of_range("Índice fora do intervalo do vetor.");
        }
        return elementos_[i - inicio_];
    }

    const Tipo& operator[](int i) const {
        if (i < inicio_ || i > fim_) {
            throw std::out_of_range("Índice fora do intervalo do vetor.");
        }
        return elementos_[i - inicio_];
    }

    ~Vetor() {
        delete[] elementos_;
    }

private:
    int inicio_;
    int fim_;
    Tipo* elementos_;
};
#endif

using std::cin;
using std::cout; 
using std::endl;
using std::string;

int main() {
  int inicio, fim;
  cin >> inicio >> fim;
  Vetor<string> v(inicio, fim);
  char opcao;
  while (cin >> opcao) {
    int indice;
    string valor;
    if (opcao == 'a') {
      cin >> indice;
      cin >> v[indice];
    } else if (opcao == 'v') {
      cin >> indice;
      cout << v[indice] << endl;
    } else if (opcao == 'r') {
      cin >> inicio >> fim;
      v.Redimensionar(inicio, fim);
    }else if (opcao=='s'){
        std::cout<<"Vetor todo:"<<std::endl<<'\t';
        for (int i=inicio;i<fim;i++){
            std::cout<<v[i]<<", ";
        }
        std::cout<<std::endl;
    } else {
      return 0;
    }
  }
  return 0;
}