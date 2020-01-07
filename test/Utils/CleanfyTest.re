open Utils.Cleanfy

// Cleanfy.clean_value
let clean_value_tests = {
  let test_trim = () => Alcotest.(check(
      string,
      "should trim string",
      "something something something",
      clean_value(" something something something ")    
    ));

  ("Cleanfy.clean_value", [
      Alcotest.test_case("With spaces", `Quick, test_trim)
  ])
}

// Suite
let suite = [
  clean_value_tests
]

// Run tests
let run = () => Alcotest.run("Cleanfy", suite)
