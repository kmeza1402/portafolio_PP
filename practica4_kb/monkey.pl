puedeTomar(estado(_, _, _, si), []).

puedeTomar(estado(PosM, PosB, suelo, no), [caminar(PosB)|Resto]) :-
    PosM \== PosB,
    puedeTomar(estado(PosB, PosB, suelo, no), Resto).

puedeTomar(estado(Pos, Pos, suelo, no), [empujar(platano)|Resto]) :-
    Pos \== platano,
    puedeTomar(estado(platano, platano, suelo, no), Resto).

puedeTomar(estado(platano, platano, suelo, no), [subir|Resto]) :-
    puedeTomar(estado(platano, platano, caja, no), Resto).

puedeTomar(estado(platano, platano, caja, no), [agarrar]) :-
    puedeTomar(estado(platano, platano, caja, si), []).