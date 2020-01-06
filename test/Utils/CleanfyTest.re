
let lowercase = a => "hello"

let test_lowercase = () => Alcotest.(
    check(string)
  )(
    "some description",
    "hello",
    lowercase("HELLO")
  )

let run = () => Alcotest.(run("Utils", [
    ("basic", [
      test_case("Lowercase", `Quick, test_lowercase)
    ])
  ])
)
