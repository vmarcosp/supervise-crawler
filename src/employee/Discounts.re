open Soup 
open Base
open Optional 

let get_value = node => leaf_text(node) 
  @?> "" 
  |> Stdlib.String.trim

let create_discounts = row => {
  let value = row 
    $$ "td" 
    |> Soup.to_list

  switch (value) {
  | [code, description, reference, earning, discount] =>
    `Assoc([
      ("code", `String(get_value(code))),
      ("description", `String(get_value(description))),
      ("reference", `String(get_value(reference))),
      ("earning", `String(get_value(earning))),
      ("discount", `String(get_value(discount))),
    ])
  | _ => `Assoc([("", `String(""))])
  }
}

let of_rows = soup =>
  soup
    $$ ".tableDados > tbody > tr" 
    |> Soup.to_list
    |> rows => List.map(rows, create_discounts)

