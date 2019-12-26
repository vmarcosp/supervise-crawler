open Soup
open Optional
open Base
open Selectors
open EmployeeTypes
open Yojson.Basic.Util

let to_href_list = list => List.map(list, node => 
  attribute("href", node) 
    @?> ""
    |> Url.with_suffix
)

let get_value = node => 
  leaf_text(node) 
    @?> ""
    |> Stdlib.String.trim

let field_of_node = item => {
  let node = item $$ "td" |> Soup.to_list

  switch node {
    | [first, second] => (get_value(first), `String(get_value(second)))
    | _ => ("label:empty", `String("value:empty"))
  }
}

let nodes_to_field = items => List.map(items, field_of_node)

let get_column = (selector, node) => 
  node 
    $$ selector
    |> Soup.to_list
    |> nodes_to_field

let get_left_column = get_column(left_column_selector)

let get_right_column = get_column(right_column_selector)

let create_employee = link => {
  let%lwt (_, body) = HttpUtils.make_request(link)
  let%lwt parsedBody = HttpUtils.body_to_string(body)
  let soup = parsedBody |> parse

  let rows = soup 
    $$ ".tableDados > tbody > tr" 
    |> Soup.to_list
  
  let all = List.map(rows, row => {
    let value = row $$ "td" |> Soup.to_list

    switch value {
    | [code, description, reference, earning, discount] =>
      `Assoc([
        ("code", `String(get_value(code))),
        ("description", `String(get_value(description))),
        ("reference", `String(get_value(reference))),
        ("earning", `String(get_value(earning))),
        ("discount", `String(get_value(discount)))
      ])
    | _ => 
      `Assoc([
        ("", `String(""))
      ])
    };
  })

  let leftColumn = get_left_column(soup)
  let rightColumn =  get_right_column(soup)
  
  let employee = `Assoc(List.concat([leftColumn, rightColumn]))
  
  Lwt.return(employee)
}

let get_data = body => {

  let links = body
    |> parse 
    $$ table_selector
    |> Soup.to_list
    |> to_href_list

  let list = List.map(links, create_employee)
  
  //  Temp
  let%lwt last = List.last(list) @?> Lwt.return(`Assoc([("", `String(""))]))

  Lwt.return(list)
}
