I vincoli obbligatori per il progetto sono i seguenti:
1. Definizione ed utilizzo di una gerarchia G di tipi che soddisfi i seguenti requisiti:
(a) G include almeno 3 diversi tipi istanziabili
(b) G include almeno una classe astratta
(c) G ha altezza ≥ 2
Ad esempio, in una gerarchia che modella degli oggetti catalogabili in una biblioteca, una classe astratta LibraryItem puo essere un `
supertipo di Libro, Rivista, Quotidiano, mentre Settimanale e Mensile possono essere sottotipi di Rivista.
Per la definizione della gerarchia G usare la fantasia ed ispirarsi ai propri interessi nello scegliere la realta da modellare mediante i `
tipi della gerarchia.
2. Definizione ed utilizzo di un opportuno template di classe C<T>, con relativi iteratori, i cui oggetti rappresentano un contenitore di
oggetti di tipo parametrico T. Vi e un unico ovvio requisito da rispettare per il template ` C<T>: non e permesso l’utilizzo dei contenitori `
STL/Qt (o di altre librerie). Si scelga l’implementazione di C<T> ritenuta piu opportuna per usare il contenitore come struttura dati `
della propria applicazione.
3. Definizione di un template di classe DeepPtr<T> di puntatori polimorfi “smart” al tipo T che implementa una gestione automatica della memoria in modalita “profonda” (deep copy/assignment/destructor) per puntatori polimorfi a T, quindi richiedendo che T sia un tipo
che supporti clonazione e distruzione polimorfa. Si tratta quindi di definire una versione semplificata del tipo std::unique ptr<T>
introdotto da C++11 (si veda ad esempio http://www.cplusplus.com/reference/memory/unique_ptr).
4. Utilizzo del contenitore C<T> per memorizzare puntatori polimorfi smart ai tipi della gerarchia G, ovvero C memorizza oggetti di tipo
DeepPtr<B> dove B e qualche tipo base della gerarchia ` G.
5. Il front-end dell’applicazione deve essere una GUI sviluppata nel framework Qt.
6. Obbligatorio per progetti in coppia: Definizione di opportune funzionalita di input/output su file per alcuni dati gestiti dall’applicazione. Non e richiesto l’uso obbligatorio della libreria standard di I/O, e' anche possibile valutare l’opportunita' di usare le classi per
l’I/O fornite da Qt. Per il formato dei file di I/O si possono considerare formati come XML, JSON o altri formati per lo scambio di
dati (AXON, YAML, etc.)

https://elearning.unipd.it/math/pluginfile.php/88483/mod_resource/content/1/specificaProgetto_PaO_20-21.pdf
