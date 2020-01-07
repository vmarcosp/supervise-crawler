open Utils.Url

let with_suffix_tests = {
  let test_with_suffix = () => Alcotest.(check(
    string,
    "should concatenate the base url with the suffix param",
    "http://service1.publica.inf.br/clientes/blumenau_cm/pt/?test=url-suffix",
    with_suffix("?test=url-suffix")
  ))

  Alcotest.("with_suffix", [
    test_case("Suffix url", `Quick, test_with_suffix)
  ])
}

let suite = [ with_suffix_tests ]

let run = () => Alcotest.run("Url", suite)
