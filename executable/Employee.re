open Soup
open Optional
open Base
open Selectors
open EmployeeTypes

let href_of_node = node => 
  attribute("href", node) 
    @?> ""
    |> Url.with_suffix

let to_href_list = list => List.map(list, href_of_node)

let get_value = node => 
  leaf_text(node) 
    @?> ""
    |> Stdlib.String.trim

let field_of_node = item => {
  let node = item $$ "td" |> to_list

  switch node {
    | [first, second] => (get_value(first), get_value(second))
    | _ => ("label:empty", "value:empty")
  }
}

let nodes_to_field = items => List.map(items, field_of_node)

let get_column = (selector, node) => 
  node 
    |> parse
    $$ selector
    |> to_list
    |> nodes_to_field

let get_left_column = get_column(left_column_selector)

let get_right_column = get_column(right_column_selector)

let create_employee = link => {
  let%lwt (_, body) = HttpUtils.make_request(link)
  let%lwt node = HttpUtils.body_to_string(body)
  
  let data = {
    leftColumn: get_left_column(node),
    rightColumn: get_right_column(node)
  }

  Lwt.return(data)
}

let get_data = body => {

  let links = body
    |> parse 
    $$ table_selector
    |> to_list
    |> to_href_list

  let list = List.map(links, create_employee)
  
  let%lwt last = List.last(list) @?> Lwt.return({
    leftColumn: [("", "")],
    rightColumn: [("", "")]
  })

  Console.log(list)

  Lwt.return(list)
}
