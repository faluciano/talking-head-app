use esp_idf_svc::hal::delay::FreeRtos;
use esp_idf_svc::hal::gpio::*;
use esp_idf_svc::hal::peripherals::Peripherals;
use esp_idf_svc::sys::EspError;

fn main() -> Result<(), EspError> {
    // It is necessary to call this function once. Otherwise some patches to the runtime
    // implemented by esp-idf-sys might not link properly. See https://github.com/esp-rs/esp-idf-template/issues/71
    esp_idf_svc::sys::link_patches();

    // Bind the log crate to the ESP Logging facilities
    esp_idf_svc::log::EspLogger::initialize_default();

    log::info!("Hello, world!");

    let peripherals = Peripherals::take()?;

    let pins: Pins = peripherals.pins;

    let red_pin: Gpio18 = pins.gpio18;
    let green_pin: Gpio19 = pins.gpio19;
    let blue_pin: Gpio21 = pins.gpio21;

    // Set the pins to output mode

    let mut red = PinDriver::output(red_pin)?;
    let mut green = PinDriver::output(green_pin)?;
    let mut blue = PinDriver::output(blue_pin)?;

    loop {
        red.set_high()?;
        FreeRtos::delay_ms(1000);
        red.set_low()?;
        FreeRtos::delay_ms(1000);

        green.set_high()?;
        FreeRtos::delay_ms(1000);
        green.set_low()?;
        FreeRtos::delay_ms(1000);

        blue.set_high()?;
        FreeRtos::delay_ms(1000);
        blue.set_low()?;
        FreeRtos::delay_ms(1000);
    }
}
