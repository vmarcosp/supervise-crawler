module Cleanfy = App__Cleanfy
open TestFramework

describe("Cleanfy", ({test}) => {
  test("should be return a value", ({expect}) => {
    expect.int(1 + 1).toBe(2);
  });
});
