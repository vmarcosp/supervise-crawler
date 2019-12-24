open Soup
open Optional
open Base

let left_column_selector = "#colEsq > table > tbody > tr"
let table_selector = ".tableDados > tbody > tr > td > a"

let href_of_node = node => 
  attribute("href", node) 
  @?> ""
  |> Url.with_suffix

let to_href_list = list => List.map(list, href_of_node)

let get_value = node =>  (node |> leaf_text) @?> ""

let to_baka = item => {
  let node = item $$ "td" |> to_list

  switch node {
    | [first, second] => (get_value(first), get_value(second))
    | _ => ("label:empty", "value:empty")
  }
}

let to_baka_list = items => List.map(items, to_baka)

let get_column = (selector, node) => 
  node 
    |> parse
    $$ selector
    |> to_list
    |> to_baka_list

let get_left_column = get_column(left_column_selector)
let get_right_column = get_column(left_column_selector)

type employeeData = {
  leftColumn: list((string, string)),
  rightColumn: list((string, string))
}

let get_data = body => {

  let links = body
    |> parse 
    $$ table_selector
    |> to_list
    |> to_href_list

  let list = List.map(links, link => {
    
    let%lwt (_, body) = HttpUtils.make_request(link)
    let%lwt node = HttpUtils.body_to_string(body)
    
    let leftColumn = get_left_column(node)
    let rightColumn = get_right_column(node)

    Lwt.return({
      leftColumn,
      rightColumn
    })
  })

  Lwt.return(list)
}
