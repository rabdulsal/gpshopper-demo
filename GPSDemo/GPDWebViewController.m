//
//  GPDWebViewController.m
//  GPSDemo
//
//  Created by James Lee on 10/10/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDWebViewController.h"

@interface GPDWebViewController () <UIWebViewDelegate>
@property (strong, nonatomic) IBOutlet UIActivityIndicatorView *loadingSpinner;

@end

@implementation GPDWebViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.url = _url;

    
    if ([self isModal]) {
        UIBarButtonItem *exitButton = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"exit"]
                                                                       style:UIBarButtonItemStyleDone
                                                                      target:self
                                                                      action:@selector(dismissSelf)];
        self.navigationItem.leftBarButtonItem = exitButton;
    }
    
    if (self.webView && self.url) {
        NSURLRequest *request = [NSURLRequest requestWithURL:self.url];
        self.loadingSpinner.hidden = NO;
        [self.webView loadRequest:request];
    }

    self.navigationController.navigationBar.tintColor = [UIColor darkGrayColor];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)dismissSelf
{
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (BOOL)isModal
{
    return self.presentingViewController.presentedViewController == self
    || self.navigationController.presentingViewController.presentedViewController == self.navigationController;
}

#pragma mark Protocol UIWebViewDelegate

- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    self.loadingSpinner.hidden = YES;
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    self.loadingSpinner.hidden = YES;
}

@end
