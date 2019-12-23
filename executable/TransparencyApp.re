open Cohttp_lwt_unix;
open Lwt;
open Lwt.Infix;
open Soup;

let table_selector = ".tableDados > tbody > tr > td > a"

let make_request = url => 
  url
  |>Uri.of_string
  |>Client.get

let get_final_url = response =>
    Cohttp.(
      response
        |> Response.headers
        |> headers => Header.get(headers, "location")
        |> Base.Option.value(~default="")
        |> url => Url.base_url ++ url 
    )

let start_crawler = response => { 
  let%lwt (_, body) = response|>get_final_url|>make_request
  let%lwt parsed_body = Cohttp_lwt.Body.to_string(body)

  let node = parsed_body
    |> parse
    $  table_selector
    |> leaf_text
    |> Base.Option.value(~default="")

  print_endline(node)

  return()
}

let main = {
  let url = Url.create_url(10, 2018)
  let%lwt (response,_) = make_request(url)

  start_crawler(response)
}

Lwt_main.run(main) |> ignore
