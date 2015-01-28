//
//  GPDLoginViewController.m
//  GPShopper-iOS
//
//  Created by Matthew Reed on 10/28/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDLoginViewController.h"
#import "GPDRegistrationViewController.h"
#import <GPShopper/GPShopper.h>

@interface GPDLoginViewController ()
{
    SCRegistrationState *state;
    SCProfile *profile;
    SCSession *session;
}

@property (strong, nonatomic) IBOutlet UITextField *usernameTextField;
@property (strong, nonatomic) IBOutlet UIBarButtonItem *cancelButton;
@property (strong, nonatomic) IBOutlet UIActivityIndicatorView *loginSpinner;
@property (weak, nonatomic) IBOutlet UIButton *loginButton;

@end

@implementation GPDLoginViewController
@synthesize usernameTextField;
@synthesize loginSpinner;

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        state = [SCRegistrationState defaultState];
        profile = [SCProfile defaultProfile];
        session = [SCSession defaultSession];
    }
    return self;
}


- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    self.loginButton.layer.cornerRadius = 2;
    self.navigationItem.leftBarButtonItem = self.cancelButton;
    self.title = @"Login";
}

- (void)sessionUpdated {
    if (session.exists) {
        [profile addObserver:self forKeyPath:@"fetchStatus" options:0 context:nil];
        [profile fetch];
    }
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"scsession_updated" object:session];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)cancelButtonPressed:(id)sender {
    [state clear];
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)loginButtonPressed:(id)sender {
    NSRegularExpression *regex = [[NSRegularExpression alloc] initWithPattern:@"^[A-Z0-9a-z._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}$" options:(NSRegularExpressionCaseInsensitive) error:nil];
    NSTextCheckingResult *match = [regex firstMatchInString:usernameTextField.text options:0 range:NSMakeRange(0, [usernameTextField.text length])];
    
    if  ([usernameTextField.text isEqualToString:@""]) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:@"You must enter an email" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
        [alert show];
    } else if (!match) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:@"Please enter a valid email." delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
        [alert show];
    } else {
        loginSpinner.hidden = NO;
        [state addObserver:self forKeyPath:@"status" options:0 context:nil];
        [state loginWithIdentifier:usernameTextField.text zipcode:@""];
    }
}

- (IBAction)createAccountButtonPressed:(id)sender {
    GPDRegistrationViewController *vc = [[GPDRegistrationViewController alloc] initWithNibName:@"GPDRegistrationViewController" bundle:nil];
    [self.navigationController pushViewController:vc animated:YES];
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context {
    if ([keyPath isEqualToString:@"status"]) {
        if (state.status == SCRegStatusSuccess) {
            [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(sessionUpdated) name:@"scsession_updated" object:session];
            [session create];
            [state removeObserver:self forKeyPath:@"status"];
        }
    } else if ([keyPath isEqualToString:@"fetchStatus"]) {
        if (profile.fetchStatus == SCProfileRemoteSuccess) {
            if (!profile.firstName) {
                UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:@"You don't have an account" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
                [alert show];
                [profile removeObserver:self forKeyPath:@"fetchStatus"];
                [session destroy];
            } else {
                loginSpinner.hidden = YES;
                UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:@"You have been logged in" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
                [alert show];
                [self dismissViewControllerAnimated:YES completion:nil];
                [profile removeObserver:self forKeyPath:@"fetchStatus"];
            }
        }
    }
}

@end
