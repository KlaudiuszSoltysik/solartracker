const { exec } = require("child_process");
require("dotenv").config({ path: "./.env.local" });

exec(
    `netsh.exe interface ip show address "${process.env.LOCAL_CONNECTION_INTERFACE_NAME}"`,
    (error, stdout, stderr) => {
        if (error) {
            return;
        }
        if (stderr) {
            return;
        }

        const lines = stdout.split("\n");
        for (const line of lines) {
            if (line.includes(process.env.LOCAL_CONNECTION_IPV4_SEARCH)) {
                const matches = line.match(/\b\d{1,3}(\.\d{1,3}){3}\b/g);
                if (matches && matches.length > 0) {
                    console.log(matches[0]);
                    return;
                }
            }
        }

    }
);