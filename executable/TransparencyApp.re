open Cohttp_lwt_unix
open Lwt
open Lwt.Infix
open Soup

let tableSelector = ".tableDados>tbody>tr>td>a"

let makeRequest = url => 
  url
  |>Uri.of_string
  |>Client.get

let getFinalUrl = response =>
    Cohttp.(
      response
        |> Response.headers
        |> headers => Header.get(headers, "location")
        |> Base.Option.value(~default="")
        |> finalUrl => Url.baseUrl++finalUrl 
    )

let startCrawler = response => { 
  let%lwt (_, body) = response|>getFinalUrl|>makeRequest
  let%lwt parsedBody = Cohttp_lwt.Body.to_string(body)

  let nodeValue = parsedBody
    |>parse
    $ tableSelector
    |>leaf_text
    |>Base.Option.value(~default="")

  print_endline(nodeValue)
  return()
}

let main = {
  let url = Url.createUrl(10, 2018)
  let%lwt (response,_) = makeRequest(url)

  startCrawler(response)
}

Lwt_main.run(main) |> ignore
