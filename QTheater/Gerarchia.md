Admin (controller)
	Prima apertura -> imposta tutti i prezzi e qta nome bevanda e nome cibo (es. patatine, coca cola, pop corn)

Cassa (controller) -> gestisce la vendita di ProdottoVendibile

ProdottoVendibile (abstract)
	-> Cibo [Nome, Prezzo, Quantità]
	-> EntrataFilm	[Titolare, Prezzo,Ridotto(bool)]
		-> Biglietto [Film, Posto,] (prezzo determinato in base a Film)
		-> Abbonamento [Numero, EntrateRimanenti, Scadenza]

ShopManager (magazzino) -> container di ProdottoVendibile

Film -> [Titolo, AumentoPrezzo, Scadenza, Durata, Genere, LimiteEta]

Sala -> [Posti (vector), MaxPosti, NomeSala]
