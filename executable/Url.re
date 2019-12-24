let base_url = "http://service1.publica.inf.br/clientes/blumenau_cm/pt/";

let with_suffix = url => base_url ++ url

let create_url = (month, year) =>
  Printf.sprintf(
    "http://service1.publica.inf.br/clientes/blumenau_cm/pt/?chaveBuscaGeral=&nr_mes=%i&nr_ano=%i&ds_nome_colaborador=&ds_local=&ds_cargo=&id_situacao=&iVinculoFiltroPeloCampo=&selPaginaAtual=1&registros_pagina=1000&p=5",
    month,
    year,
  );
