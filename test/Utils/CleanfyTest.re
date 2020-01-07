open Utils.Cleanfy

// Cleanfy.clean_value
let clean_value_tests = {
  let test_trim = () => Alcotest.(check(
      string,
      "should trim string",
      "something something something",
      clean_value(" something something something ")    
    ));

  let test_invalid_characters = () => Alcotest.(check(
    string,
    "should remove invalid chars",
    "something",
    clean_value("something []2[2")
  ));

  ("Cleanfy.clean_value", [
      Alcotest.test_case("With spaces", `Quick, test_trim),
      Alcotest.test_case("With invalid chars", `Quick, test_invalid_characters)
  ])
}

// Suite
let suite = [
  clean_value_tests
]

// Run tests
let run = () => Alcotest.run("Cleanfy", suite)
