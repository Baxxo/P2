Admin (controller)
	Prima apertura -> imposta tutti i prezzi e qta nome bevanda e nome cibo (es. patatine, coca cola, pop corn)

Cassa (controller) -> gestisce la vendita di ProdottoVendibile

Utente [Nome,Eta,Telefono]

ProdottoVendibile (abstract)[Nome,Prezzo,Qta]
	-> Cibo [ValoriNutrizionali]
	-> EntrataFilm	[Utente]
		-> Biglietto [Film, Posto, Ridotto(bool)] (prezzo determinato in base a Film)
		-> Abbonamento [Numero, EntrateRimanenti, Scadenza] (quando viene scalata un'entrata verrà creato Biglietto con prezzo=0)

ShopManager -> container di ProdottoVendibile(magazzino), container per prodotti acquistati(scontrino), container per Utenti(utenti)

Film -> [Titolo, AumentoPrezzo, Scadenza, Durata, Genere, LimiteEta, Sala]

Sala -> [Posti (vector), MaxPosti, NomeSala]
