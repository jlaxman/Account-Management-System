# Read the fixed width format file
data <- read.fwf("portfolio_history.txt", widths = c(16, 16, 16, 16), stringsAsFactors = FALSE)

colnames(data) <- c("balance", "totalBalance", "seconds", "date")

data$seconds <- as.POSIXct(data$seconds, origin="1970-01-01", tz="EST")

data$totalBalance <- as.numeric(data$totalBalance)

# Calculate the change in total balance
data$totalBalanceChange <- c(NA, diff(data$totalBalance))

# Convert time back to seconds for plotting
data$secondsNumeric <- as.numeric(data$seconds - as.POSIXct("1970-01-01", tz="EST"))

# Plotting the total balanc(stock+ cash balance) over time
plot(data$secondsNumeric, data$totalBalance, type='b', col='#05e71f', xlab='Time (seconds)', ylab='Total Portfolio over time', main='Total Portfolio(Stock + Balance) over time')

#Plotting the change in total balance over time
data <- na.omit(data)
plot(data$secondsNumeric, data$totalBalanceChange, type='b', col='#e29504', xlab='Time (seconds)', ylab='Change in Total Portfolio Value', main='Change in Total Potfolio Value over Time')
