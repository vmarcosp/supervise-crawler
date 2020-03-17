open Soup
open Optional
open Base
open Selectors
open Yojson.Basic.Util

let default_employee = Lwt.return(`Assoc([("", `String(""))]))

let to_href_list = list =>
  List.map(list, node => 
    attribute("href", node)   
      @?> "" 
      |> Url.with_suffix
  )

let get_value = node => leaf_text(node)
  @?> "" 
  |> Stdlib.String.trim

let field_of_node = item => {
  let node = item 
    $$ "td" 
    |> Soup.to_list

  switch (node) {
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
  let%lwt (response, body) = HttpUtils.make_request(link)
  let%lwt parsedBody = HttpUtils.body_to_string(body)

  let soup = parsedBody|>parse

  let discounts = Discounts.of_rows(soup)
  let left_column = get_left_column(soup)
  let right_column = get_right_column(soup)

  let employee = List.concat([
      left_column, 
      right_column, 
      [("discounts", `List(discounts))] 
    ])

  Console.log(`Assoc(employee) |> Yojson.pretty_to_string)

  Lwt.return(`Assoc(employee))
}

let get_data = body => {
  let links = body 
    |> parse $$ table_selector 
    |> Soup.to_list 
    |> to_href_list

  let list = List.map(links, create_employee)
  let%lwt last = List.last(list) @?> default_employee
  
  Lwt.return(list)
}
