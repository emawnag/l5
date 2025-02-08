const responseBodies = new Map();

chrome.webRequest.onBeforeRequest.addListener(
    function (details) {
        if (details.url.includes("channel?gsessionid=")) {
            const filter = chrome.webRequest.filterResponseData(details.requestId);
            const decoder = new TextDecoder("utf-8");
            let data = "";

            filter.ondata = event => {
                data += decoder.decode(event.data, { stream: true });
            };

            filter.onstop = () => {
                responseBodies.set(details.requestId, data);
                filter.write(new TextEncoder().encode(data));
                filter.disconnect();
            };
        }
    },
    { urls: ["https://akb48-tp.tenten.tw/*","https://firestore.googleapis.com/*"] },
    ["blocking"]
);

chrome.webRequest.onCompleted.addListener(
    async function (details) {
        if (details.url.includes("channel?gsessionid=")) {
            console.log("URL:", details.url);
            try {
                const responseBody = getCapturedResponseBody(details.requestId);
                const blob = new Blob([responseBody], { type: 'application/octet-stream' });

                console.log("Blob:", blob);
            } catch (error) {
                console.error("Error processing the response:", error);
            }
        }
    },
    { urls: ["https://firestore.googleapis.com/google.firestore.v1.Firestore/Listen/channel?gsessionid=*",
        "https://akb48-tp.tenten.tw/*"] }
);

function getCapturedResponseBody(requestId) {
    return responseBodies.get(requestId) || "response body data";
}

console.log("background.js loaded");
